#include "model/InputReader.h"

using namespace ShapeFlow;

InputReader::InputData::InputData()
{
    radius=3;
    iterations=10;

    neighborhood=InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
    ld = InputData::ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
    ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
    cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
    sm = InputData::ODRConfigInput::SpaceMode::Pixel;
    levels= this->radius;
    optRegionInApplication = false;
    seType = InputData::ODRConfigInput::StructuringElementType::RECT;


    fp = InputData::FlowProfile::DoubleStep;

    dtWeight = 0.5;
    sqWeight = 1.0;
    lgWeight = 0.2;
    penalizationWeight = 0.0;

    optMethod = InputData::OptMethod::Improve;

    shape = Shape(ShapeType::Square);
    gridStep=1.0;

    excludeOptPointsFromAreaComputation = false;
    penalizationMode = PenalizationMode::No_Penalization;
}

InputReader::InputData InputReader::readInput(int argc,char** argv)
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"r:i:a:c:s:p:n:dl:q:t:g:m:oS:y:h:z:x"))!=-1)
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
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowProfile::SingleStepConvexities;
                else if(strcmp(optarg,"double")==0 ) id.fp = InputData::FlowProfile::DoubleStep;
                else if(strcmp(optarg,"single-opt")==0 ) id.fp = InputData::FlowProfile::SingleStepOpt;
                else if(strcmp(optarg,"double-opt")==0 ) id.fp = InputData::FlowProfile::DoubleStepOpt;
                else if(strcmp(optarg,"single-inner")==0 ) id.fp = InputData::FlowProfile::SingleStepInner;
                else if(strcmp(optarg,"double-inner")==0 ) id.fp = InputData::FlowProfile::DoubleStepInner;
                else if(strcmp(optarg,"single-around-inner")==0 ) id.fp = InputData::FlowProfile::SingleStepAroundInner;
                else if(strcmp(optarg,"double-around-inner")==0 ) id.fp = InputData::FlowProfile::DoubleStepAroundInner;
                else std::runtime_error("Profile not recognized.");
                break;
            case 'n':
            {
                int n = atoi(optarg);
                if(n==4) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
                else if(n==8) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::EightNeighborhood;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            }
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
                if(strcmp(optarg,"triangle")==0) id.shape = Shape( ShapeType::Triangle);
                else if(strcmp(optarg,"square")==0) id.shape = Shape( ShapeType::Square );
                else if(strcmp(optarg,"pentagon")==0) id.shape = Shape( ShapeType::Pentagon);
                else if(strcmp(optarg,"heptagon")==0) id.shape = Shape( ShapeType::Heptagon);
                else if(strcmp(optarg,"ball")==0) id.shape = Shape( ShapeType::Ball);
                else if(strcmp(optarg,"ellipse")==0) id.shape = Shape( ShapeType::Ellipse);
                else if(strcmp(optarg,"flower")==0) id.shape = Shape( ShapeType::Flower);
                else id.shape = Shape(ShapeType::UserDefined,optarg);
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
            case 'x':
            {
                id.excludeOptPointsFromAreaComputation = true;
                break;
            }
            case 'z':
            {
                id.penalizationMode = InputData::PenalizationMode::Penalize_Ones;
                id.penalizationWeight = std::atof(optarg);
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
                        "[-x Exclude opt points from computation area default: false] \n"
                        "[-z Penalization weight default: 0.0] \n"
                        "FLOW_OUTPUT_FOLDER " << std::endl;
                exit(1);
        }
    }

    id.outputFolder = argv[optind];
    return id;
}