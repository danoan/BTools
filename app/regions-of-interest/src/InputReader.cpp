#include "InputReader.h"

namespace RegionsOfInterest{
InputData::InputData()
{
  shape = Shape(ShapeType::Square);
  gridStep = 1.0;

  radius=3;

  levels=-1;
  levelDefinition = LevelDefinition::LD_FartherFromCenter;
  optBand=1;
}

InputData readInput(int argc, char** argv)
{
  InputData id;

  int opt;
  while( (opt=getopt(argc,argv,"S:h:r:l:o:"))!=-1)
  {
    switch(opt)
    {
      case 'S':
        if(strcmp(optarg,"triangle")==0) id.shape = InputData::Shape( InputData::ShapeType::Triangle);
        else if(strcmp(optarg,"square")==0) id.shape = InputData::Shape( InputData::ShapeType::Square );
        else if(strcmp(optarg,"pentagon")==0) id.shape = InputData::Shape( InputData::ShapeType::Pentagon);
        else if(strcmp(optarg,"heptagon")==0) id.shape = InputData::Shape( InputData::ShapeType::Heptagon);
        else if(strcmp(optarg,"ball")==0) id.shape = InputData::Shape( InputData::ShapeType::Ball);
        else if(strcmp(optarg,"ellipse")==0) id.shape = InputData::Shape( InputData::ShapeType::Ellipse);
        else if(strcmp(optarg,"flower")==0) id.shape = InputData::Shape( InputData::ShapeType::Flower);
        else if(strcmp(optarg,"wave")==0) id.shape = InputData::Shape( InputData::ShapeType::Wave);
        else if(strcmp(optarg,"bean")==0) id.shape = InputData::Shape( InputData::ShapeType::Bean );
        else id.shape = InputData::Shape(InputData::ShapeType::UserDefined,optarg);
        break;
      case 'h':
      {
        id.gridStep = std::atof(optarg);
        break;
      }
      case 'r':
        id.radius = atoi(optarg);
        break;
      case 'l':
        id.levels= std::atof(optarg);
        if(id.levels<0) id.levelDefinition = InputData::LevelDefinition::LD_FartherFromCenter;
        else id.levelDefinition = InputData::LevelDefinition::LD_CloserFromCenter;
        id.levels = fabs(id.levels);
        break;
      case 'o':
        id.optBand = atoi(optarg);
        break;
      default:
        std::cerr << "Usage: OutputFilepath \n"
                     "[-S Shape (triangle square pentagon heptagon ball ellipse ball wave bean). Default: square\n"
                     "[-h Grid step (default:1.0)]\n"
                     "[-r Ball Radius default 3] \n"
                     "[-l Application level. default: -1] \n"
                     "[-o Optimization band. default: 1] \n"
                  << std::endl;
        exit(1);
    }
  }
  id.outputFilepath = argv[optind];
  return id;
}

}

