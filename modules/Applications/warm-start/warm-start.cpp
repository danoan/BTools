#include <DGtal/helpers/StdDefs.h>

#include "DIPaCUS/base/Shapes.h"

#include "BTools/core/model/input/BCApplicationInput.h"
#include "BTools/core/model/input/SolutionHint.h"
#include "BTools/core/model/BCAOutput.h"

#include "FlowControl.h"
#include "InputReader.h"
#include "Types.h"

using namespace DGtal::Z2i;
using namespace BTools::Core;
using namespace WarmStart;

DigitalSet resolveShape(Shape shape,double gridStep)
{
    int radius=20;
    if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
    else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
    else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
    else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
    else
    {
        cv::Mat img = cv::imread(shape.imagePath,CV_8UC1);
        Domain domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(img.cols-1,img.rows-1) );
        DigitalSet ds(domain);
        DIPaCUS::Representation::CVMatToDigitalSet(ds,img,1);
        return ds;
    }
}

struct PointValue
{
    PointValue(Point p, double v):p(p),v(v){}

    Point p;
    double v;

    bool operator<(const PointValue& other)
    {
        return this->v < other.v;
    }
};

SolutionHint solutionHint(const DigitalSet& ds,
                                     const InputReader::InputData& id,
                                     const InputReader::InputData::FlowProfile flowProfile,
                                     const std::string& outputFolder,
                                     const std::string& suffix)
{
    typedef InputReader::InputData::ODRConfigInput ODRConfigInput;
    int levels=1;
    ODRConfigInput::LevelDefinition ld = ODRConfigInput::LevelDefinition::LD_FartherFromCenter;

    FlowControl::BCConfigInput bcInput(id.radius,
                                       0,
                                       1.0,
                                       0.0,
                                       0,
                                       id.excludeOptPointsFromAreaComputation,
                                       id.penalizationMode,
                                       InputReader::InputData::OptMethod::Improve);

    FlowControl::ODRConfigInput odrConfigInput(InputReader::InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL,
                                               InputReader::InputData::ODRConfigInput::CountingMode::CM_PIXEL,
                                               InputReader::InputData::ODRConfigInput::SpaceMode::Pixel,
                                               id.radius,
                                               id.gridStep,
                                               levels,
                                               ld,
                                               id.neighborhood,
                                               id.seType,
                                               id.opt);

    Point size = ds.domain().upperBound() - ds.domain().lowerBound() + Point(1,1);

    cv::Mat currentImage = cv::Mat::zeros(size(1),size(0),CV_8UC1);
    DIPaCUS::Representation::digitalSetToCVMat(currentImage,ds);


    MockDistribution frDistr;
    MockDistribution bkDistr;

    ImageDataInput imageDataInput(frDistr,
                                  bkDistr,
                                  currentImage,
                                  currentImage);

    BCApplicationInput bcaInput(bcInput,
                                imageDataInput,
                                odrConfigInput,
                                flowProfile);

    BCApplicationOutput bcaOutput(bcaInput);


    BTools::Visitors::PotentialMap* v = new BTools::Visitors::PotentialMap(outputFolder + "/map_" + suffix+ ".svg");

    std::vector<IBCControlVisitor*> visitors = { v };
    BCApplication BCA(bcaOutput,
                      bcaInput,
                      1,
                      false,
                      visitors.begin(),
                      visitors.end());

    auto pv = v->pv;
    std::vector<PointValue> pvVector;
    for(auto it=pv.begin();it!=pv.end();++it)
    {
        pvVector.push_back( PointValue(it->first,it->second));
    }

    std::sort(pvVector.begin(),pvVector.end());//Crescent order
    DigitalSet ones(imageDataInput.inputDomain);
    DigitalSet zeros(imageDataInput.inputDomain);

    int total = pvVector.size();
    int numHints = std::ceil(total*id.warmStartPercentage);
    for(int i=0;i<numHints;++i)
    {
            zeros.insert(pvVector[i].p);
            ones.insert(pvVector[total-1-i].p);
    }
    return SolutionHint(ones,zeros);
}

void drawHint(const DigitalSet& ds, const SolutionHint& shint, const std::string& outputFolder, const std::string& suffix)
{
    DGtal::Board2D board;


    board << DGtal::SetMode( ds.className(), "Paving" );
    board << ds;

    board << DGtal::SetMode( ds.begin()->className(), "Paving" );
    std::string specificStyle = ds.begin()->className() + "/Paving";
    for(auto it=shint.ones.begin();it!=shint.ones.end();++it)
    {
        board << DGtal::CustomStyle( specificStyle,
                                            new DGtal::CustomColors(DGtal::Color::Black,
                                                                    DGtal::Color::Green));

        board << *it;
    }

    for(auto it=shint.zeros.begin();it!=shint.zeros.end();++it)
    {
        board << DGtal::CustomStyle( specificStyle,
                                     new DGtal::CustomColors(DGtal::Color::Black,
                                                             DGtal::Color::Black));
        board << *it;
    }

    boost::filesystem::create_directories(outputFolder);
    board.saveSVG( (outputFolder + "/" + suffix + ".svg").c_str(),200,200,2 );
}

int main(int argc, char*argv[])
{
    InputReader::InputData id = InputReader::readInput(argc,argv);
    DigitalSet _ds = resolveShape(id.shape,id.gridStep);

    boost::filesystem::create_directories(id.outputFolder);
    std::string currImagePath = id.outputFolder + "/" + BTools::Utils::nDigitsString(0,4) + ".pgm";

    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));
    Domain flowDomain = ds.domain();


    BTools::Utils::exportImageFromDigitalSet(ds,flowDomain,currImagePath);

    InputReader::InputData::FlowProfile flowProfile = InputReader::InputData::FlowProfile::SingleStepConvexities;

    int it = 1;
    while(it < id.iterations)
    {
        if(it%2==1) flowProfile = InputReader::InputData::FlowProfile::SingleStepConvexities;
        else flowProfile = InputReader::InputData::FlowProfile::SingleStepConcavities;

        std::string suffix = BTools::Utils::nDigitsString(it,4);
        SolutionHint shint = solutionHint(ds,id,flowProfile,id.outputFolder + "/potentialMap",suffix);

        drawHint(ds,shint,id.outputFolder + "/hints" ,suffix);


        FlowControl::BCConfigInput bcInput(id.radius,
                                           0,
                                           1.0,
                                           0.0,
                                           0,
                                           id.excludeOptPointsFromAreaComputation,
                                           id.penalizationMode,
                                           InputReader::InputData::OptMethod::Improve);

        FlowControl::ODRConfigInput odrConfigInput(InputReader::InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL,
                                                   InputReader::InputData::ODRConfigInput::CountingMode::CM_PIXEL,
                                                   InputReader::InputData::ODRConfigInput::SpaceMode::Pixel,
        id.radius,
                id.gridStep,
                id.levels,
                id.ld,
                id.neighborhood,
                id.seType,
                id.opt);

        Point size = ds.domain().upperBound() - ds.domain().lowerBound() + Point(1,1);

        cv::Mat currentImage = cv::Mat::zeros(size(1),size(0),CV_8UC1);
        DIPaCUS::Representation::digitalSetToCVMat(currentImage,ds);


        MockDistribution frDistr;
        MockDistribution bkDistr;

        ImageDataInput imageDataInput(frDistr,
                                      bkDistr,
                                      currentImage,
                                      currentImage);

        BCApplicationInput bcaInput(bcInput,
                                    imageDataInput,
                                    odrConfigInput,
                                    flowProfile);

        BCApplicationOutput bcaOutput(bcaInput);

        std::vector<IBCControlVisitor*> visitors;
        BCApplication BCA(bcaOutput,
                          bcaInput,
                          1,
                          false,
                          visitors.begin(),
                          visitors.end(),
                          shint);

        BTools::Utils::exportImageFromDigitalSet( bcaOutput.energySolution.outputDS,id.outputFolder + "/" + suffix + ".pgm"  );
        ds.clear();
        ds.insert(bcaOutput.energySolution.outputDS.begin(),bcaOutput.energySolution.outputDS.end());

        ++it;
    }


    return 0;
}