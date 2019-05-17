#include "InputReader.h"

using namespace RegionsOfInterest;

InputReader::InputData::InputData()
{
    radius=3;
    neighborhood= ODRConfigInput::NeighborhoodType::FourNeighborhood;
    ld = ODRConfigInput::LevelDefinition::LD_CloserFromCenter;

    ac = ODRConfigInput::ApplicationCenter::AC_PIXEL;
    cm = ODRConfigInput::CountingMode::CM_PIXEL;
    sm = ODRConfigInput::SpaceMode::Pixel;

    om = ODRModel::OptimizationMode::OM_CorrectConvexities;
    am = ODRModel::ApplicationMode::AM_AroundBoundary;

    seType = ODRConfigInput::StructuringElementType::RECT;

    fp = FlowProfile::DoubleStep;

    levels=3;
    optRegionInApplication = false;

    shape = Shape(ShapeType::Square);
    gridStep = 1.0;
}

void InputReader::usage(char* argv[])
{
    std::cout << "Usage: " << argv[0] <<  "OUTPUT_PATH [options] \n"
              << "[-S shape (triangle square pentagon heptagon ball ellipse flower) Default: square]\n"
              << "[-r radius (default:3)]\n"
              << "[-a computation center (pixel,pointel,linel) (default:pixel)]\n"
              << "[-c counting mode (pixel,pointel) (default:pixel)]\n"
              << "[-s space mode (pixel,interpixel) (default:pixel)]\n"
              << "[-p FlowProfile (single double single-opt double-opt single-inner double-inner) (default double)]\n"
              << "[-n neighborhood (4,8) (default:4)]\n"
              << "[-l levels (positive means levels grows from contour; negative leans that levels grows towards the contour (default:3)]\n"
              << "[-o include optimization region in the computation region (default:false)]\n"
              << "[-y Structuring element type (rect cross) (default:rect)]\n"
              << "[-h Grid step (default:1.0)]\n";

}

InputReader::InputData InputReader::readInput(int argc,char** argv)
{
    if(argc <2)
    {
        usage(argv);
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
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowProfile::SingleStepConvexities;
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
                if(strcmp(optarg,"triangle")==0) id.shape = Shape( ShapeType::Triangle);
                else if(strcmp(optarg,"square")==0) id.shape = Shape( ShapeType::Square );
                else if(strcmp(optarg,"pentagon")==0) id.shape = Shape( ShapeType::Pentagon);
                else if(strcmp(optarg,"heptagon")==0) id.shape = Shape( ShapeType::Heptagon);
                else if(strcmp(optarg,"ball")==0) id.shape = Shape( ShapeType::Ball);
                else if(strcmp(optarg,"ellipse")==0) id.shape = Shape( ShapeType::Ellipse);
                else if(strcmp(optarg,"flower")==0) id.shape = Shape( ShapeType::Flower);
                else id.shape = Shape(ShapeType::UserDefined,optarg);
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
                usage(argv);
                exit(1);
            }
        }
    }

    id.outputFilepath = argv[optind++];

    return id;
}