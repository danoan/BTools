#include "InputReader.h"

using namespace BTools::Application::Illustration;

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{

    int opt;
    while( (opt=getopt(argc,argv,"a:c:s:p:r:i:"))!=-1)
    {
        switch(opt)
        {
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
            case 'r':
                id.radius = atoi(optarg);
                break;
            case 'i':
                id.iterations= atoi(optarg);
                break;

            default:
                std::cerr << "Usage: [-r Ball Radius] "
                        "[-i Max Iterations] "
                        "[-a Application Center 0 Pixel 1 Pointel] "
                        "[-c Counting Mode 0 Pixel 1 Pointel] "
                        "[-s Space Mode 0 Pixel 1 Interpixel] "
                        "[-p FlowProfile single double] "
                        "FLOW_NAME" << std::endl;
                exit(1);
        }

        id.flowName = argv[optind];
    }
}