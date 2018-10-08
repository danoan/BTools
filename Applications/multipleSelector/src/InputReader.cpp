#include "InputReader.h"

using namespace BTools::Application::MultipleSelector;

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{

    int opt;
    while( (opt=getopt(argc,argv,"c:d:l:b:i:"))!=-1)
    {
        switch(opt)
        {
            default:
                std::cerr << "Usage: multipleSelector IMAGE_DATASET_PATH" << std::endl;
        }
    }

    id.datasetPath= argv[optind];
}