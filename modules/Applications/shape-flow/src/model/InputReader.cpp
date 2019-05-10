#include "model/InputReader.h"

using namespace ShapeFlow;

void InputReader::defaultValues(InputData& id)
{
    id.radius=3;
    id.iterations=10;
    id.useDigitalArea = false;


    id.neighborhood=InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
    id.ld = InputData::ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
    id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
    id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
    id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
    id.levels=id.radius;
    id.optRegionInApplication = false;
    id.seType = InputData::ODRConfigInput::StructuringElementType::RECT;


    id.fp = InputData::FlowProfile::DoubleStep;

    id.dtWeight = 0.5;
    id.sqWeight = 1.0;
    id.lgWeight = 0.2;

    id.optMethod = InputData::OptMethod::Improve;

    id.shape = Shape::Square;
    id.gridStep=1.0;
}

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{
    defaultValues(id);

    int opt;
    while( (opt=getopt(argc,argv,"r:i:a:c:s:p:n:dl:q:t:g:m:oS:y:h:"))!=-1)
    {
        switch(opt)
        {
            case 'r':
                id.radius = atoi(optarg);
                break;
            case 'i':
                id.iterations= atoi(optarg);
                break;
            case 'a':
                if(strcmp(optarg,"pixel")==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
                else if(strcmp(optarg,"pointel")==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_POINTEL;
                else if(strcmp(optarg,"linel")==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_LINEL;
                break;
            case 'c':
                if(strcmp(optarg,"pixel")==0) id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
                else if(strcmp(optarg,"pointel")==0) id.cm = InputData::ODRConfigInput::CountingMode::CM_POINTEL;
                break;
            case 's':
                if(strcmp(optarg,"pixel")==0) id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
                else if(strcmp(optarg,"interpixel")==0) id.sm = InputData::ODRConfigInput::SpaceMode::Interpixel;
                break;
            case 'p':
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowProfile::SingleStep;
                else if(strcmp(optarg,"double")==0 ) id.fp = InputData::FlowProfile::DoubleStep;
                else if(strcmp(optarg,"single-opt")==0 ) id.fp = InputData::FlowProfile::SingleStepOpt;
                else if(strcmp(optarg,"double-opt")==0 ) id.fp = InputData::FlowProfile::DoubleStepOpt;
                else if(strcmp(optarg,"single-inner")==0 ) id.fp = InputData::FlowProfile::SingleStepInner;
                else if(strcmp(optarg,"double-inner")==0 ) id.fp = InputData::FlowProfile::DoubleStepInner;
                else if(strcmp(optarg,"single-around-inner")==0 ) id.fp = InputData::FlowProfile::SingleStepAroundInner;
                else if(strcmp(optarg,"double-around-inner")==0 ) id.fp = InputData::FlowProfile::DoubleStepAroundInner;
                break;
            case 'n':
            {
                int n = atoi(optarg);
                if(n==4) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
                else if(n==8) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::EightNeighborhood;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            }
            case 'd':
                id.useDigitalArea=true;
                break;
            case 'l':
                id.levels = atoi(optarg);
                if(id.levels<0) id.ld = InputData::ODRConfigInput::LevelDefinition::LD_FartherFromCenter;
                else id.ld = id.ld = InputData::ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
                id.levels = abs(id.levels);
                break;
            case 'q':
                id.sqWeight = atof(optarg);
                break;
            case 't':
                id.dtWeight = atof(optarg);
                break;
            case 'g':
                id.lgWeight = atof(optarg);
                break;
            case 'm':
                if(strcmp(optarg,"probe")==0) id.optMethod = InputData::OptMethod::Probe;
                else if(strcmp(optarg,"improve")==0) id.optMethod = InputData::OptMethod::Improve;
                break;
            case 'o':
                id.optRegionInApplication = true;
                break;
            case 'S':
                if(strcmp(optarg,"triangle")==0) id.shape = Shape::Triangle;
                else if(strcmp(optarg,"square")==0) id.shape = Shape::Square;
                else if(strcmp(optarg,"pentagon")==0) id.shape = Shape::Pentagon;
                else if(strcmp(optarg,"heptagon")==0) id.shape = Shape::Heptagon;
                else if(strcmp(optarg,"ball")==0) id.shape = Shape::Ball;
                else if(strcmp(optarg,"ellipse")==0) id.shape = Shape::Ellipse;
                else if(strcmp(optarg,"flower")==0) id.shape = Shape::Flower;
                else if(strcmp(optarg,"dumbell")==0) id.shape = Shape::Dumbell;
                else throw std::runtime_error("Unrecognized shape!");
                break;
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
                std::cerr << "Usage: \n[-r Ball Radius default 3] \n"
                        "[-i Max Iterations default 10] \n"
                        "[-a Computation Center (pixel or linel or pointel) default pixel] \n"
                        "[-c Counting Mode (pixel or pointel) default pixel] \n"
                        "[-s Space Mode (pixel or interpixel) default pixel] \n"
                        "[-p FlowProfile single double single-opt double-opt single-inner double-inner default double] \n"
                        "[-n Neighborhood 4 or 8 default: 4] \n"
                        "[-d Use digital area default: false] \n"
                        "[-l Computation levels. If negative, select LD_FartherFromCenter. Default: Ball radius] \n"
                        "[-q Squared Curvature Term weight default: 1.0] \n"
                        "[-t Data Term weight default: 1.0] \n"
                        "[-g Length Term weight default: 1.0] \n"
                        "[-m Opt method 'probe' 'improve' default: improve] \n"
                        "[-o Include optimization region in the application region default: false \n"
                        "[-S Shape (triangle square pentagon heptagon ball ellipse ball dumbell). Default: square\n"
                        "[-t Structuring element type (rect cross) (default:rect)]\n"
                        "[-h Grid step (default:1.0)]\n"
                        "FLOW_OUTPUT_FOLDER " << std::endl;
                exit(1);
        }
    }

    id.outputFolder = argv[optind];
}