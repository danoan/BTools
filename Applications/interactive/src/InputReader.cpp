#include "InputReader.h"

using namespace BTools::Application::Interactive;

void InputReader::defaultValues(InputData& id)
{
    id.radius=3;
    id.iterations=10;
    id.useDigitalArea = false;
    id.neighborhood=InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
    id.levels=id.radius;
    id.ld = InputData::ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
    id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
    id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
    id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
    id.fp = InputData::FlowProfile::DoubleStep;

    id.dtWeight = 0.5;
    id.sqWeight = 1.0;
    id.lgWeight = 0.2;

    id.optMethod = InputData::OptMethod::Probe;

    id.invertFrgBkg = false;
    id.optRegionInApplication = false;
}

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{
    defaultValues(id);

    int opt;
    while( (opt=getopt(argc,argv,"r:i:a:c:s:p:n:dl:q:t:g:ox"))!=-1)
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
                if(atoi(optarg)==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
                else if(atoi(optarg)==1) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_POINTEL;
                else if(atoi(optarg)==2) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_LINEL;
                break;
            case 'c':
                if(atoi(optarg)==0) id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
                else if(atoi(optarg)==1) id.cm = InputData::ODRConfigInput::CountingMode::CM_POINTEL;
                break;
            case 's':
                if(atoi(optarg)==0) id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
                else if(atoi(optarg)==1) id.sm = InputData::ODRConfigInput::SpaceMode::Interpixel;
                break;
            case 'p':
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowProfile::SingleStep;
                else if(strcmp(optarg,"double")==0 ) id.fp = InputData::FlowProfile::DoubleStep;
                else if(strcmp(optarg,"single-opt")==0 ) id.fp = InputData::FlowProfile::SingleStepOpt;
                else if(strcmp(optarg,"double-opt")==0 ) id.fp = InputData::FlowProfile::DoubleStepOpt;
                break;
            case 'n':
            {
                int n = atoi(optarg);
                if (n == 4) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
                else if (n == 8) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::EightNeighborhood;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            }
            case 'd':
                id.useDigitalArea=true;
                break;
            case 'l':
                id.levels = atoi(optarg);
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
            case 'x':
                id.invertFrgBkg = true;
                break;
            default:
                std::cerr << "Usage: [-r Ball Radius default 3] "
                        "[-i Max Iterations default 10] "
                        "[-a Computation Center 0 Pixel 1 Pointel default Pixel] "
                        "[-m Computation Mode 'around' 'opt' default 'around'] "
                        "[-c Counting Mode 0 Pixel 1 Pointel default Pixel] "
                        "[-s Space Mode 0 Pixel 1 Interpixel default Pixel] "
                        "[-p FlowProfile single double single-opt double-opt single-inner double-inner default double] "
                        "[-n Neighborhood 4 or 8 default: 4] "
                        "[-d Use digital area default: false] "
                        "[-l Computation levels default. if negative, select LD_FartherFromCenter: Ball radius] "
                        "[-q Squared Curvature Term weight default: 1.0] "
                        "[-t Data Term weight default: 1.0] "
                        "[-g Length Term weight default: 1.0] "
                        "[-m Opt method 'probe' 'improve' default: probe] "
                        "[-o Include optimization region in the application region default: false "
                        "[-x Invert foreground with background default: false "
                        "FLOW_NAME FLOW_FOLDER " << std::endl;
                exit(1);
        }
    }


    id.imageFilePath = argv[optind];
}