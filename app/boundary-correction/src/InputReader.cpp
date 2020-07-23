#include "InputReader.h"

using namespace BoundaryCorrection;

InputReader::InputData::InputData()
{
  radius=3;
  iterations=10;

  dtWeight = 0.5;
  sqWeight = 1.0;
  lgWeight = 0.2;

  levels=-1;
  levelDefinition = LevelDefinition::LD_FartherFromCenter;

  initialDilation=10;

  showIterations=false;
  showProgress=false;
}

InputReader::InputData InputReader::readInput(int argc, char** argv)
{
  InputData id;

  int opt;
  while( (opt=getopt(argc,argv,"r:i:q:t:g:so:vd:l:"))!=-1)
  {
    switch(opt)
    {
      case 'r':
        id.radius = atoi(optarg);
        break;
      case 'i':
        id.iterations= atoi(optarg);
        break;
      case 'q':
        id.sqWeight = atof(optarg);
        break;
      case 't':
        id.dtWeight = atof(optarg);
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
      case 'd':
        id.initialDilation = std::atoi(optarg);
        break;
      case 'l':
        id.levels= std::atof(optarg);
        if(id.levels<0) id.levelDefinition = InputData::LevelDefinition::LD_FartherFromCenter;
        else id.levelDefinition = InputData::LevelDefinition::LD_CloserFromCenter;
        id.levels = fabs(id.levels);
        break;
      default:
        std::cerr << "Usage: GRABCUT_FILE_PATH \n"
                     "[-r Ball Radius default 3] \n"
                     "[-i Max Iterations default 10] \n"
                     "[-q Squared Curvature Term weight default: 1.0] \n"
                     "[-t Data Term weight default: 1.0] \n"
                     "[-g Length Term weight default: 1.0] \n"
                     "[-s Show iterations default: false] \n"
                     "[-o Output folder default: \"\" (no output generated)] \n"
                     "[-v Show progress status default: false] \n"
                     "[-d Initial dilation size: default: 10] \n"
                     "[-l Application level. default: -1] \n"
                  << std::endl;
        exit(1);
    }
  }


  id.grabcutFile = argv[optind];
  return id;
}