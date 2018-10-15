#include "InputReader.h"

using namespace BTools::Application::Illustration;

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{

    int opt;
    while( (opt=getopt(argc,argv,"l:r:i:"))!=-1)
    {
        switch(opt)
        {
            case 'l':
                id.levelSets= atoi(optarg);
                break;
            case 'r':
                id.radius = atoi(optarg);
                break;
            case 'i':
                id.iterations= atoi(optarg);
                break;

            default:
                std::cerr << "Usage: [-r Ball Radius] "
                        "[-l Level sets] "
                        "[-i Max Iterations]" << std::endl;
                exit(1);
        }
    }
}