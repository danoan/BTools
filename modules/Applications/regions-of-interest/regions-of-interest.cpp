#include <SCaBOliC/Core/ODRInterface.h>
#include <BTools/core/pool/ODRPool.h>
#include <BTools/core/pool/FlowPool.h>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <boost/filesystem.hpp>
#include <DGtal/io/writers/GenericWriter.h>

#include "InputReader.h"

using namespace RegionsOfInterest;
using namespace DGtal::Z2i;
using namespace BTools::Core;
using namespace SCaBOliC::Core;

ODRInterface& getFactory(const InputReader::InputData& id)
{
    ODRConfigInput odrConfigInput(id.ac,id.cm,id.sm,id.radius,id.gridStep,id.levels,
            id.ld,id.neighborhood,id.seType,id.optRegionInApplication);

    return ODRPool::get(odrConfigInput);
}

IFlowProfile& getProfile(const InputReader::InputData& id)
{
    return FlowPool::getFlow(id.fp,id.optRegionInApplication);
}

DigitalSet getShape(Shape shape,double gridStep)
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

void saveODR(const ODRModel& ODR,std::string outputPath)
{
    DGtal::Board2D board;
    std::string specificStyle = ODR.original.className() + "/Paving";
    board << DGtal::SetMode(ODR.original.className(),"Paving");

//    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Silver));
//    board << ODR.trustBKG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Blue, DGtal::Color::Blue));
    board << ODR.trustFRG;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Green, DGtal::Color::Green));
    board << ODR.optRegion;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Red, DGtal::Color::Red));
    board << ODR.applicationRegion;

    DigitalSet optAppIntersection(ODR.optRegion.domain());
    DIPaCUS::SetOperations::setIntersection(optAppIntersection,ODR.optRegion,ODR.applicationRegion);

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Yellow, DGtal::Color::Yellow));
    board << optAppIntersection;

    board.saveSVG(outputPath.c_str(),200,200,10);

}

int main(int argc, char* argv[])
{

    InputReader::InputData id = InputReader::readInput(argc,argv);

    ODRInterface& factory = getFactory(id);
    IFlowProfile& profile = getProfile(id);


    const IFlowStepConfig& flowStepConfig = profile.nextStep();
    ODRModel odrModel = factory.createODR(flowStepConfig.optimizationMode(),
                                          flowStepConfig.applicationMode(),
                                          getShape(id.shape,id.gridStep),
                                          id.optRegionInApplication);


    boost::filesystem::path p(id.outputFilepath);
    boost::filesystem::create_directories(p.remove_filename());
    saveODR(odrModel,id.outputFilepath);

    return 0;
}
