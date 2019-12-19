#include "InputReader.h"

using namespace BoundaryCorrection;

InputReader::InputData::InputData()
{
    radius=3;
    iterations=10;
    optBand=3;
    levels=-1;
    ld = ODRConfigInput::LevelDefinition::LD_FartherFromCenter;

    dtWeight = 0.5;
    sqWeight = 1.0;
    lgWeight = 0.2;

    excludeOptPointsFromAreaComputation = false;
    uniformPerimeter = false;
    initialDilation=10;

    optMethod = InputData::OptMethod::Improve;
    showIterations=false;
    showProgress=false;
}

InputReader::InputData InputReader::readInput(int argc, char** argv)
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"r:i:q:t:g:m:so:vxd:w:uO:l:"))!=-1)
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
            case 'm':
                if(strcmp(optarg,"probe")==0) id.optMethod = InputData::OptMethod::Probe;
                else if(strcmp(optarg,"improve")==0) id.optMethod = InputData::OptMethod::Improve;
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
            case 'x':
                id.excludeOptPointsFromAreaComputation = true;
                break;
            case 'd':
                id.initialDilation = std::atoi(optarg);
                break;
            case 'u':
                id.uniformPerimeter = true;
                break;
            case 'w':
                id.pixelMaskFilepath = optarg;
                break;
            case 'O':
                id.optBand = std::atof(optarg);
                break;
            case 'l':
                id.levels= std::atof(optarg);
                if(id.levels<0) id.ld = InputData::LevelDefinition::LD_FartherFromCenter;
                else id.ld = InputData::LevelDefinition::LD_CloserFromCenter;
                id.levels = fabs(id.levels);                 
                break;                
            default:
                std::cerr << "Usage: GRABCUT_FILE_PATH \n"
                        "[-r Ball Radius default 3] \n"
                        "[-i Max Iterations default 10] \n"
                        "[-q Squared Curvature Term weight default: 1.0] \n"
                        "[-t Data Term weight default: 1.0] \n"
                        "[-g Length Term weight default: 1.0] \n"
                        "[-m Opt method 'probe' 'improve' default: improve] \n"
                        "[-s Show iterations default: false] \n"
                        "[-o Output folder default: \"\" (no output generated)] \n"
                        "[-v Show progress status default: false] \n"
                        "[-x Exclude opt points from computation area default: false] \n"
                        "[-d Initial dilation size: default: 10] \n"
                        "[-u Uniform perimeter: default: false] \n"
                        "[-w Pixel mask path] \n"
                        "[-O Optimization band size. default: 3] \n"
                        "[-l Application level. default: -1] \n"
                        << std::endl;
                exit(1);
        }
    }


    id.grabcutFile = argv[optind];
    return id;
}