#include "InputReader.h"

using namespace BoundaryCorrection;

void InputReader::defaultValues(InputData& id)
{
    id.radius=3;
    id.iterations=10;

    id.dtWeight = 0.5;
    id.sqWeight = 1.0;
    id.lgWeight = 0.2;

    id.optMethod = InputData::OptMethod::Improve;
    id.showIterations=false;
    id.showProgress=false;
}

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{
    defaultValues(id);

    int opt;
    while( (opt=getopt(argc,argv,"r:i:q:t:g:m:so:v"))!=-1)
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
            case 'b':
                id.showProgress = true;
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
                        << std::endl;
                exit(1);
        }
    }


    id.grabcutFile = argv[optind];
}
