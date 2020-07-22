#include "io/InputReader.h"

namespace ShapeFlow{
InputData::InputData()
{
  shape = Shape(ShapeType::Square);
  gridStep = 1.0;

  radius=3;
  iterations=10;

  sqWeight = 1.0;
  lgWeight = 0.0;

  levels=-1;
  levelDefinition = LevelDefinition::LD_FartherFromCenter;

  showIterations=false;
  showProgress=false;
}

InputData readInput(int argc, char** argv)
{
  InputData id;

  int opt;
  while( (opt=getopt(argc,argv,"S:h:r:i:q:g:so:vl:"))!=-1)
  {
    switch(opt)
    {
      case 'S':
        if(strcmp(optarg,"triangle")==0) id.shape = Shape( ShapeType::Triangle);
        else if(strcmp(optarg,"square")==0) id.shape = Shape( ShapeType::Square );
        else if(strcmp(optarg,"pentagon")==0) id.shape = Shape( ShapeType::Pentagon);
        else if(strcmp(optarg,"heptagon")==0) id.shape = Shape( ShapeType::Heptagon);
        else if(strcmp(optarg,"ball")==0) id.shape = Shape( ShapeType::Ball);
        else if(strcmp(optarg,"ellipse")==0) id.shape = Shape( ShapeType::Ellipse);
        else if(strcmp(optarg,"flower")==0) id.shape = Shape( ShapeType::Flower);
        else if(strcmp(optarg,"wave")==0) id.shape = Shape( ShapeType::Wave);
        else if(strcmp(optarg,"bean")==0) id.shape = Shape( ShapeType::Bean );
        else id.shape = Shape(ShapeType::UserDefined,optarg);
        break;
      case 'h':
      {
        id.gridStep = std::atof(optarg);
        break;
      }
      case 'r':
        id.radius = atoi(optarg);
        break;
      case 'i':
        id.iterations= atoi(optarg);
        break;
      case 'q':
        id.sqWeight = atof(optarg);
        break;
      case 'g':
        id.lgWeight = atof(optarg);
        break;
      case 's':
        id.showIterations = true;
        break;
      case 'o':
        id.outputFolder = optarg;
        break;
      case 'v':
        id.showProgress = true;
        break;
      case 'l':
        id.levels= std::atof(optarg);
        if(id.levels<0) id.levelDefinition = InputData::LevelDefinition::LD_FartherFromCenter;
        else id.levelDefinition = InputData::LevelDefinition::LD_CloserFromCenter;
        id.levels = fabs(id.levels);
        break;
      default:
        std::cerr << "Usage: \n"
                     "[-S Shape (triangle square pentagon heptagon ball ellipse ball wave bean). Default: square\n"
                     "[-h Grid step (default:1.0)]\n"
                     "[-r Ball Radius default 3] \n"
                     "[-i Max Iterations default 10] \n"
                     "[-q Squared Curvature Term weight default: 1.0] \n"
                     "[-g Length Term weight default: 1.0] \n"
                     "[-s Show iterations default: false] \n"
                     "[-o Output folder default: \"\" (no output generated)] \n"
                     "[-v Show progress status default: false] \n"
                     "[-l Application level. default: -1] \n"
                  << std::endl;
        exit(1);
    }
  }
  return id;
}

}

