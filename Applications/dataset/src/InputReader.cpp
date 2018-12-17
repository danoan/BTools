#include "InputReader.h"

using namespace BTools::Application::Dataset;

void InputReader::defaultValues(InputData& id)
{
    id.radius=3;
    id.iterations=10;
    id.useDigitalArea = false;
    id.neighborhood=InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
    id.levels=id.radius;
    id.am = InputData::ODRConfigInput::ApplicationMode::AM_AroundBoundary;
    id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
    id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
    id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
    id.fp = InputData::FlowProfile::DoubleStep;

    id.dtWeight = 0.5;
    id.sqWeight = 1.0;
    id.lgWeight = 0.2;
}

void InputReader::readInput(InputData& id,
                            int argc,
                            char** argv)
{
    defaultValues(id);

    int opt;
    while( (opt=getopt(argc,argv,"r:i:a:m:c:s:p:n:dl:q:t:g:"))!=-1)
    {
        switch(opt)
        {
            case 'r':
                id.radius = atoi(optarg);
                break;
            case 'i':
                id.iterations= atoi(optarg);
                break;
            case 'a':
                if(atoi(optarg)==0) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_PIXEL;
                else if(atoi(optarg)==1) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_POINTEL;
                else if(atoi(optarg)==2) id.ac = InputData::ODRConfigInput::ApplicationCenter::AC_LINEL;
                break;
            case 'm':
                if(strcmp(optarg,"around")==0) id.am = InputData::ODRConfigInput::ApplicationMode::AM_AroundBoundary;
                else if(strcmp(optarg,"opt")==0) id.am = InputData::ODRConfigInput::ApplicationMode::AM_OptimizationBoundary;
                break;
            case 'c':
                if(atoi(optarg)==0) id.cm = InputData::ODRConfigInput::CountingMode::CM_PIXEL;
                else if(atoi(optarg)==1) id.cm = InputData::ODRConfigInput::CountingMode::CM_POINTEL;
                break;
            case 's':
                if(atoi(optarg)==0) id.sm = InputData::ODRConfigInput::SpaceMode::Pixel;
                else if(atoi(optarg)==1) id.sm = InputData::ODRConfigInput::SpaceMode::Interpixel;
                break;
            case 'p':
                if(strcmp(optarg,"single")==0 ) id.fp = InputData::FlowProfile::SingleStep;
                else if(strcmp(optarg,"double")==0 ) id.fp = InputData::FlowProfile::DoubleStep;
                break;
            case 'n':
            {
                int n = atoi(optarg);
                if(n==4) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::FourNeighborhood;
                else if(n==8) id.neighborhood = InputData::ODRConfigInput::NeighborhoodType::EightNeighborhood;
                else throw std::runtime_error("Neighborhood value must be 4 or 8.");
                break;
            }
            case 'd':
                id.useDigitalArea=true;
                break;
            case 'l':
                id.levels = atoi(optarg);
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
            default:
                std::cerr << "Usage: fromSeed [-r Ball Radius default 3] "
                        "[-i Max Iterations default 10] "
                        "[-a Computation Center 0 Pixel 1 Pointel default Pixel] "
                        "[-m Computation Mode 'around' 'opt' default 'around'] "
                        "[-c Counting Mode 0 Pixel 1 Pointel default Pixel] "
                        "[-s Space Mode 0 Pixel 1 Interpixel default Pixel] "
                        "[-p FlowProfile single double default double] "
                        "[-n Neighborhood 4 or 8 default: 4] "
                        "[-d Use digital area default: false] "
                        "[-l Computation levels default: Ball radius] "
                        "[-q Squared Curvature Term weight default: 1.0] "
                        "[-t Data Term weight default: 1.0] "
                        "[-g Length Term weight default: 1.0] "
                        "DATA_SET_PATH " << std::endl;
                exit(1);
        }
    }

    id.datasetPath= argv[optind];
}