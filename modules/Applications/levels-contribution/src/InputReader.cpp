#include "InputReader.h"

using namespace MostExternContribution;

InputReader::InputData::InputData()
{
    radius=3;
    iterations=10;

    seType = InputData::ODRConfigInput::StructuringElementType::RECT;

    shape = Shape::Square;
    gridStep=1.0;

    levels=0;
    ld = ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
    opt=false;

    neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;

    excludeOptPointsFromAreaComputation = false;
    penalizationMode = PenalizationMode::No_Penalization;
}

InputReader::InputData InputReader::readInput(int argc,
                                              char** argv)
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"r:i:n:S:y:h:l:xzo"))!=-1)
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
                else throw std::runtime_error("Unrecognized shape!");
                break;
            case 'n':
            {
                int n = atoi(optarg);
                if(n==4) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
                else if(n==8) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::EightNeighborhood;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            }
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
            case 'l':
            {
                id.levels = std::atoi(optarg);
                id.opt=false;

                if(id.levels<0)
                {
                    id.ld = InputData::ODRConfigInput::LevelDefinition::LD_FartherFromCenter;
                    id.levels=-id.levels;
                }
                else if(id.levels>0)
                {
                    id.ld = InputData::ODRConfigInput::LevelDefinition::LD_CloserFromCenter;
                }
                else
                {
                    id.opt = true;
                }

                break;
            }
            case 'o':
            {
                id.opt = true;
                break;
            }
            case 'x':
            {
                id.excludeOptPointsFromAreaComputation = true;
                break;
            }
            case 'z':
            {
                id.penalizationMode = InputData::PenalizationMode::Penalize_Ones;
                break;
            }
            default:
                std::cerr << "Usage: \n[-r Ball Radius default 3] \n"
                        "[-i Max Iterations default 10] \n"
                        "[-S Shape (triangle square pentagon heptagon ball ellipse ball dumbell). Default: square\n"
                        "[-y Structuring element type (rect cross) (default:rect)]\n"
                        "[-n Neighborhood 4 or 8 default: 4] \n"
                        "[-h Grid step (default:1.0)]\n"
                        "[-l Computation levels. If negative, select LD_FartherFromCenter. Default: Ball radius] \n"
                        "[-x Exclude opt points from computation area default: false] \n"
                        "[-z Penalize changes default: false] \n"
                        "OUTPUT_FOLDER " << std::endl;
                exit(1);
        }
    }

    id.outputFolder = argv[optind];
    return id;
}