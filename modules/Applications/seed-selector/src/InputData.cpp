#include "InputData.h"

namespace SeedSelector
{
    void usage(char* argv[])
    {
        std::cerr << "Usage: ./" << argv[0] << "imagePath outputFolder\n\n";
    }

    InputData readInput(int argc, char* argv[])
    {
        if(argc<3)
        {
            usage(argv);
            exit(1);
        }

        InputData id;

        char opt;
        while( (opt=getopt(argc,argv,"ou:f:b:"))!=-1)
        {
            switch(opt)
            {
                case 'o':
                {
                    id.once = true;
                    break;
                }
                case 'u':
                {
                    id.unknownImageMask=optarg;
                    break;
                }
                case 'f':
                {
                    id.fgImageMask=optarg;
                    break;
                }
                case 'b':
                {
                    id.bgImageMask=optarg;
                    break;
                }
                default:
                {
                    usage(argv);
                    exit(1);
                    break;
                }
            }
        }

        id.imagePath = argv[optind++];
        id.outputFolder = argv[optind++];


        return id;
    }
}