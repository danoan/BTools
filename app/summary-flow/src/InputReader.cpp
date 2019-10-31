#include "summary-flow/InputReader.h"

namespace SummaryFlow
{
    namespace InputReader
    {
        void usage(int argc,char* argv[])
        {
            std::cerr << "Usage " << argv[0] << ": FlowImagesFolderPath OutputFilePath \n"
            << "-j [Jump step (default: 5) ]\n"
            << "-p [ path to pixelMask ]\n"
            << "-d [ path to dirsMask ]\n";
        }

        InputData readInput(int argc, char* argv[])
        {
            if(argc<3)
            {
                usage(argc,argv);
                exit(1);
            }

            InputData id;
            int opt;

            while( (opt=getopt(argc,argv,"j:p:d:") )!=-1 )
            {
                switch(opt)
                {
                    case 'j':
                    {
                        id.jumpStep = std::atoi(optarg);
                        break;
                    }
                    case 'p':
                    {
                        id.pixelMaskPath = optarg;
                        break;
                    }
                    case 'd':
                    {
                        id.dirsMaskPath = optarg;
                        break;
                    }
                    default:
                    {
                        usage(argc,argv);
                        exit(1);
                    }
                }
            }

            id.flowImagesFolderPath = argv[optind++];
            id.outputFilePath = argv[optind++];

            std::string extension = boost::filesystem::path(id.outputFilePath).extension().string();

            if(strcmp(".svg",extension.c_str())==0) id.iot= ImageOutputType::SVG;
            else if(strcmp(".eps",extension.c_str())==0) id.iot= ImageOutputType::EPS;
            else throw std::runtime_error("Output type not recognized!");

            return id;

        }
    }
}