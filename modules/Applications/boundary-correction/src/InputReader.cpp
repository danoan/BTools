#include "InputReader.h"

using namespace BoundaryCorrection;

InputReader::InputData::InputData()
{
    radius=3;
    iterations=10;

    dtWeight = 0.5;
    sqWeight = 1.0;
    lgWeight = 0.2;
    penalizationWeight = 0.0;

    excludeOptPointsFromAreaComputation = false;
    penalizationMode = InputData::PenalizationMode::No_Penalization;

    optMethod = InputData::OptMethod::Improve;
    showIterations=false;
    showProgress=false;
}

InputReader::InputData InputReader::readInput(int argc, char** argv)
{
    InputData id;

    int opt;
    while( (opt=getopt(argc,argv,"r:i:q:t:g:m:so:vxz:"))!=-1)
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
            case 'z':
                id.penalizationMode = InputData::PenalizationMode::Penalize_Ones;
                id.penalizationWeight = std::atof(optarg);
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
                        "[-z Penalization weight default: 0.0] \n"
                        << std::endl;
                exit(1);
        }
    }


    id.grabcutFile = argv[optind];
    return id;
}