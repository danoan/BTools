#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "OneImageFlow.h"

using namespace SummaryFlow;

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cerr << "Usage " << argv[0] << " Flow_Images_Folder_Path Output_Name [Jump_Step] [svg (default) eps]" <<std::endl;
        exit(1);
    }

    int jumpStep = 2;
    OneImageFlow::ImageOutputType iot=OneImageFlow::SVG;
    if(argc==4) jumpStep = atoi(argv[3]);
    if(argc==5)
    {
        if(strcmp("svg",argv[4])==0) iot= OneImageFlow::SVG;
        else if(strcmp("eps",argv[4])==0) iot= OneImageFlow::EPS;
        else throw std::runtime_error("Output type not recognized!");
    }

    std::string flowImagesFolderPath = argv[1];
    std::string outputName = argv[2];
    boost::filesystem::path srcImagePath( flowImagesFolderPath );

    std::string name = srcImagePath.stem().string();
    std::string outputImagePath = srcImagePath.string() + "/" + outputName;
    OneImageFlow oif(srcImagePath.string(),outputImagePath,jumpStep,iot);

    return 0;
}