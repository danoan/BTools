#include "InputReader.h"

using namespace BTools::Application::MultipleSelector;

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{

    int opt;
    while( (opt=getopt(argc,argv,"h"))!=-1)
    {
        switch(opt)
        {
            case 'h':
                std::cerr << "Usage: multipleSelector IMAGE_DATASET_PATH" << std::endl;
        }
    }

    id.datasetPath= argv[optind];
}