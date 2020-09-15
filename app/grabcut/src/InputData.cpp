#include "InputData.h"

namespace GrabCut
{
void usage(char* argv[])
{
  std::cerr << "Usage: ./" << argv[0] << " imgPath fgSeedMask bgSeedMask outputObjectPath\n"
            << "[-i Grabcut iterations (default: 1)]\n"
            << "[-u unknownSeedMaskPath]\n"
            << "[-s lastSegmentationMask]\n"
            << "[-o outputSegPath]\n"
            << "[-d show segmented image]\n\n";
}

InputData readInput(int argc, char* argv[])
{
  if(argc < 5)
  {
    usage(argv);
    exit(1);
  }

  InputData id;
  char opt;
  while( (opt=getopt(argc,argv,"u:s:o:i:d"))!=-1 )
  {
    switch(opt)
    {
      case 'u':
      {
        id.unknownMask = optarg;
        break;
      }
      case 's':
      {
        id.lastSegmentationMask = optarg;
        break;
      }
      case 'o':
      {
        id.outputSegImage = optarg;
        break;
      }
      case 'i':
      {
        id.iterations = std::atoi(optarg);
        break;
      }
      case 'd':
      {
        id.showSeg=true;
        break;
      }
      default:
      {
        usage(argv);
        exit(2);
      }
    }
  }

  id.imgPath = argv[optind++];
  id.fgSeedMask = argv[optind++];
  id.bgSeedMask = argv[optind++];
  id.outputObject = argv[optind++];

  return id;
}
}

