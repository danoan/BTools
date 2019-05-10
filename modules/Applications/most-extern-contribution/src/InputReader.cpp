#include "InputReader.h"

using namespace MostExternContribution;

InputReader::InputData::InputData()
{
    radius=3;
    iterations=10;

    seType = InputData::ODRConfigInput::StructuringElementType::RECT;

    shape = Shape::Square;
    gridStep=1.0;
}

InputReader::InputData InputReader::readInput(int argc,
                                              char** argv)
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"r:i:S:y:h:"))!=-1)
    {
        switch(opt)
        {
            case 'r':
                id.radius = atoi(optarg);
                break;
            case 'i':
                id.iterations= atoi(optarg);
                break;
            case 'S':
                if(strcmp(optarg,"triangle")==0) id.shape = Shape::Triangle;
                else if(strcmp(optarg,"square")==0) id.shape = Shape::Square;
                else if(strcmp(optarg,"pentagon")==0) id.shape = Shape::Pentagon;
                else if(strcmp(optarg,"heptagon")==0) id.shape = Shape::Heptagon;
                else if(strcmp(optarg,"ball")==0) id.shape = Shape::Ball;
                else if(strcmp(optarg,"ellipse")==0) id.shape = Shape::Ellipse;
                else if(strcmp(optarg,"flower")==0) id.shape = Shape::Flower;
                else if(strcmp(optarg,"dumbell")==0) id.shape = Shape::Dumbell;
                else throw std::runtime_error("Unrecognized shape!");
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
            default:
                std::cerr << "Usage: \n[-r Ball Radius default 3] \n"
                        "[-i Max Iterations default 10] \n"
                        "[-S Shape (triangle square pentagon heptagon ball ellipse ball dumbell). Default: square\n"
                        "[-t Structuring element type (rect cross) (default:rect)]\n"
                        "[-h Grid step (default:1.0)]\n"
                        "OUTPUT_FOLDER " << std::endl;
                exit(1);
        }
    }

    id.outputFolder = argv[optind];
    return id;
}