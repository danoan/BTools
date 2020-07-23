#include "summary-flow/input/InputReader.h"

namespace SummaryFlow
{
    namespace InputReader
    {
        void usage(int argc,char* argv[])
        {
            std::cerr << "Creates the vectorial image [OutputFilePath] (.svg or .eps) from a sequence of images located in [FlowImagesFolderPath].\n"
            << "The images are taken in alphabetic order of their names.\n\n"
            << "Usage " << argv[0] << ": FlowImagesFolderPath OutputFilePath \n"
            << "-j [Image draw interval (default: -1 (automatic)) ]\n"
            << "-e [Image extension (default: .pgm)]\n"
            << "-c [Color scheme [classic,rainy-jungle,lollipop] (default: classic)]\n"
            << "-r [Radius of the centered ball]\n"
            << "-h [Grid step of the centered ball]\n"
            << "-p [Path to pixelMaskFile]\n"
            << "-d [Path to directionMaskFile]\n";
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

            while( (opt=getopt(argc,argv,"j:e:c:p:d:r:h:") )!=-1 )
            {
                switch(opt)
                {
                    case 'j':
                    {
                        id.drawInterval = std::atoi(optarg);
                        break;
                    }
                    case 'e':
                    {
                        id.imageExtension = optarg;
                        break;
                    }
                    case 'c':
                    {
                        if(strcmp("classic",optarg)==0) id.colorScheme= DefaultColorSchemes::Classic;
                        else if(strcmp("rainy-jungle",optarg)==0) id.colorScheme= DefaultColorSchemes::RainyJungle;
                        else if(strcmp("lollipop",optarg)==0) id.colorScheme= DefaultColorSchemes::Lollipop;
                        else throw std::runtime_error("Color scheme not recognized! Choose among classic, rainy-jungle, lollipop");
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
                    case 'r':
                    {
                        id.radius = std::atof(optarg);
                        id.drawCenterBall=true;
                        break;
                    }
                    case 'h':
                    {
                        id.h= std::atof(optarg);
                        id.drawCenterBall=true;
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
            else throw std::runtime_error("Output type not recognized! The output file extension must be .svg or .eps");

            return id;

        }
    }
}