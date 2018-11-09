#include "InputReader.h"

using namespace BTools::Application::Flow;

void InputReader::defaultValues(InputData& id)
{
    id.radius=3;
    id.iterations=10;
    id.useDigitalArea = false;
    id.neighborhood=4;
    id.levels=id.radius;
    id.ac = InputData::FlowConfigInput::ApplicationCenter::AC_PIXEL;
    id.cm = InputData::FlowConfigInput::CountingMode::CM_PIXEL;
    id.sm = InputData::FlowConfigInput::SpaceMode::Pixel;
    id.fp = InputData::FlowConfigInput::FlowProfile::DoubleStep;
}

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{
    defaultValues(id);

    int opt;
    while( (opt=getopt(argc,argv,"r:i:a:c:s:p:n:dl:"))!=-1)
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
                if(atoi(optarg)==0) id.ac = InputData::FlowConfigInput::ApplicationCenter::AC_PIXEL;
                else if(atoi(optarg)==1) id.ac = InputData::FlowConfigInput::ApplicationCenter::AC_POINTEL;
                break;
            case 'c':
                if(atoi(optarg)==0) id.cm = InputData::FlowConfigInput::CountingMode::CM_PIXEL;
                else if(atoi(optarg)==1) id.cm = InputData::FlowConfigInput::CountingMode::CM_POINTEL;
                break;
            case 's':
                if(atoi(optarg)==0) id.sm = InputData::FlowConfigInput::SpaceMode::Pixel;
                else if(atoi(optarg)==1) id.sm = InputData::FlowConfigInput::SpaceMode::Interpixel;
                break;
            case 'p':
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowConfigInput::FlowProfile::SingleStep;
                else if(strcmp(optarg,"double")==0 ) id.fp = InputData::FlowConfigInput::FlowProfile::DoubleStep;
                break;
            case 'n':
                int n = atoi(optarg);
                if(n==4) id.neighborhood = 4;
                else if(n==8) id.neighborhood = 8;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            case 'd':
                id.useDigitalArea=true;
                break;
            case 'l':
                id.levels = atoi(optarg);
                break;
            default:
                std::cerr << "Usage: [-r Ball Radius] "
                        "[-i Max Iterations ] "
                        "[-a Computation Center 0 Pixel 1 Pointel] "
                        "[-c Counting Mode 0 Pixel 1 Pointel] "
                        "[-s Space Mode 0 Pixel 1 Interpixel] "
                        "[-p FlowProfile single double] "
                        "[-n Neighborhood 4 or 8] "
                        "[-d Use digital area] "
                        "[-l Computation levels] "
                        "[FLOW_NAME] {FLOW_FOLDER} " << std::endl;
                exit(1);
        }

        id.flowName = argv[optind++];
        id.outputFolder = argv[optind];
    }
}