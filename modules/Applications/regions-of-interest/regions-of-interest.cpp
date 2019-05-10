#include <unistd.h>

#include <BTools/core/model/input/ODRConfigInput.h>
#include <BTools/core/interface/IFlowProfile.h>
#include <BTools/core/profiles/FlowSingleStep.h>
#include <BTools/core/profiles/FlowDoubleStep.h>
#include <BTools/core/profiles/Correct.h>
#include <BTools/core/profiles/CorrectOpt.h>
#include <BTools/core/profiles/Expand.h>
#include <BTools/core/profiles/ExpandOpt.h>

#include <SCaBOliC/Core/ODRInterface.h>
#include <SCaBOliC/Core/ODRModel.h>
#include <SCaBOliC/Core/ODRPixels.h>
#include <SCaBOliC/Core/ODRInterpixels.h>
#include <BTools/core/pool/ODRPool.h>
#include <BTools/core/pool/FlowPool.h>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <boost/filesystem.hpp>
#include <DGtal/io/writers/GenericWriter.h>

enum Shape{Triangle,Square,Pentagon,Heptagon,Ball,Ellipse,Flower};

struct InputData
{
    typedef BTools::Core::ODRConfigInput ODRConfigInput;
    typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;
    typedef SCaBOliC::Core::ODRModel ODRModel;

    InputData()
    {
        radius=3;
        neighborhood= ODRConfigInput::NeighborhoodType::FourNeighborhood;
        ld = ODRConfigInput::LevelDefinition::LD_CloserFromCenter;

        ac = ODRConfigInput::ApplicationCenter::AC_PIXEL;
        cm = ODRConfigInput::CountingMode::CM_PIXEL;
        sm = ODRConfigInput::SpaceMode::Pixel;

        om = ODRModel::OptimizationMode::OM_OriginalBoundary;
        am = ODRModel::ApplicationMode::AM_OptimizationBoundary;

        seType = ODRConfigInput::StructuringElementType::RECT;

        fp = FlowProfile::DoubleStep;

        levels=3;
        optRegionInApplication = false;

        shape = Shape::Square;
        gridStep = 1.0;
    }
    std::string outputFilepath;

    int radius;

    ODRConfigInput::ApplicationCenter ac;
    ODRConfigInput::CountingMode cm;
    ODRConfigInput::SpaceMode  sm;
    ODRConfigInput::NeighborhoodType neighborhood;
    ODRConfigInput::LevelDefinition ld;
    ODRConfigInput::StructuringElementType  seType;

    ODRModel::OptimizationMode  om;
    ODRModel::ApplicationMode  am;

    FlowProfile fp;

    bool optRegionInApplication;
    int levels;

    Shape shape;
    double gridStep;
};

void usage()
{
    std::cout << "Usage: regions-of-interest OUTPUT_PATH [options] \n"
              << "[-S shape (triangle square pentagon heptagon ball ellipse flower) Default: square]\n"
              << "[-r radius (default:3)]\n"
              << "[-a computation center (pixel,pointel,linel) (default:pixel)]\n"
              << "[-c counting mode (pixel,pointel) (default:pixel)]\n"
              << "[-s space mode (pixel,interpixel) (default:pixel)]\n"
              << "[-p FlowProfile (single double single-opt double-opt single-inner double-inner) (default double)]\n"
              << "[-n neighborhood (4,8) (default:4)]\n"
              << "[-l levels (positive means levels grows from contour; negative leans that levels grows towards the contour (default:3)]\n"
              << "[-o include optimization region in the computation region (default:false)]\n"
              << "[-t Structuring element type (rect cross) (default:rect)]\n"
              << "[-h Grid step (default:1.0)]\n";

}

InputData readInput(int argc, char* argv[])
{
    if(argc <2)
    {
        usage();
        exit(1);
    }
    InputData id;
    int opt;
    while( (opt=getopt(argc,argv,"S:r:a:c:s:p:n:l:oy:h:"))!=-1 )
    {
        switch(opt)
        {
            case 'r':
            {
                id.radius = atoi(optarg);
                break;
            }
            case 'a':
            {
                if(strcmp(optarg,"pixel")==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
                else if(strcmp(optarg,"pointel")==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_POINTEL;
                else if(strcmp(optarg,"linel")==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_LINEL;
                break;
            }
            case 'c':
            {
                if(strcmp(optarg,"pixel")==0) id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
                else if(strcmp(optarg,"pointel")==0) id.cm = InputData::ODRConfigInput::CountingMode::CM_POINTEL;
                break;
            }
            case 's':
            {
                if(strcmp(optarg,"pixel")==0) id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
                else if(strcmp(optarg,"interpixel")==0) id.sm = InputData::ODRConfigInput::SpaceMode::Interpixel;
                break;
            }
            case 'p':
            {
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowProfile::SingleStep;
                else if(strcmp(optarg,"double")==0 ) id.fp = InputData::FlowProfile::DoubleStep;
                else if(strcmp(optarg,"single-opt")==0 ) id.fp = InputData::FlowProfile::SingleStepOpt;
                else if(strcmp(optarg,"double-opt")==0 ) id.fp = InputData::FlowProfile::DoubleStepOpt;
                else if(strcmp(optarg,"single-inner")==0 ) id.fp = InputData::FlowProfile::SingleStepInner;
                else if(strcmp(optarg,"double-inner")==0 ) id.fp = InputData::FlowProfile::DoubleStepInner;
                else if(strcmp(optarg,"single-around-inner")==0 ) id.fp = InputData::FlowProfile::SingleStepAroundInner;
                else if(strcmp(optarg,"double-around-inner")==0 ) id.fp = InputData::FlowProfile::DoubleStepAroundInner;
                break;
            }
            case 'n':
            {
                int n = atoi(optarg);
                if(n==4) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
                else if(n==8) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::EightNeighborhood;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            }
            case 'l':
            {
                id.levels = atoi(optarg);
                if(id.levels<0) id.ld = InputData::ODRConfigInput::LevelDefinition::LD_FartherFromCenter;
                else id.ld = id.ld = InputData::ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
                id.levels = abs(id.levels);
                break;
            }
            case 'o':
            {
                id.optRegionInApplication = true;
                break;
            }
            case 'S':
            {
                if(strcmp(optarg,"triangle")==0) id.shape = Shape::Triangle;
                else if(strcmp(optarg,"square")==0) id.shape = Shape::Square;
                else if(strcmp(optarg,"pentagon")==0) id.shape = Shape::Pentagon;
                else if(strcmp(optarg,"heptagon")==0) id.shape = Shape::Heptagon;
                else if(strcmp(optarg,"ball")==0) id.shape = Shape::Ball;
                else if(strcmp(optarg,"ellipse")==0) id.shape = Shape::Ellipse;
                else if(strcmp(optarg,"flower")==0) id.shape = Shape::Flower;
                else throw std::runtime_error("Unrecognized shape!");
                break;
            }
            case 'y':
            {
                if(strcmp("rect",optarg)==0) id.seType = InputData::ODRConfigInput::StructuringElementType::RECT;
                else if(strcmp("cross",optarg)==0) id.seType = InputData::ODRConfigInput::StructuringElementType::CROSS;
                else throw std::runtime_error("Structuring element type not recognized.");
                break;
            }
            case 'h':
            {
                id.gridStep = std::atof(optarg);
                break;
            }
            default:
            {
                usage();
                exit(1);
            }
        }
    }

    id.outputFilepath = argv[optind++];

    return id;
}

using namespace DGtal::Z2i;
using namespace BTools::Core;
using namespace SCaBOliC::Core;

ODRInterface& getFactory(const InputData& id)
{
    ODRConfigInput odrConfigInput(id.ac,id.cm,id.sm,id.levels,
            id.ld,id.neighborhood,id.seType,id.optRegionInApplication);

    return ODRPool::get(odrConfigInput);
}

IFlowProfile& getProfile(const InputData& id)
{
    return FlowPool::getFlow(id.fp,id.optRegionInApplication);
}

DigitalSet getShape(Shape shape,double gridStep)
{
    int radius=20;
    if(shape==Shape::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
    else if(shape==Shape::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
    else if(shape==Shape::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
    else if(shape==Shape::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
    else if(shape==Shape::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
    else if(shape==Shape::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
    else if(shape==Shape::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
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

    InputData id = readInput(argc,argv);

    ODRInterface& factory = getFactory(id);
    IFlowProfile& profile = getProfile(id);


    const IFlowStepConfig& flowStepConfig = profile.nextStep();
    ODRModel odrModel = factory.createODR(flowStepConfig.optimizationMode(),
                                          flowStepConfig.applicationMode(),
                                          (int) id.radius*(1.0/id.gridStep),
                                          getShape(id.shape,id.gridStep),
                                          id.optRegionInApplication);

    boost::filesystem::path p(id.outputFilepath);
    boost::filesystem::create_directories(p.remove_filename());
    saveODR(odrModel,id.outputFilepath);

    return 0;
}