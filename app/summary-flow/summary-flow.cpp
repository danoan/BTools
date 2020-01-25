#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "OneImageFlow.h"

using namespace SummaryFlow;

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cerr << "Usage " << argv[0] << " FlowImagesFolderPath OutputFilePath [Jump_Step]" <<std::endl;
        exit(1);
    }

    int jumpStep = -1;
    OneImageFlow::ImageOutputType iot=OneImageFlow::SVG;
    if(argc>=4) jumpStep = atoi(argv[3]);

    std::string flowImagesFolderPath = argv[1];
    std::string outputFilePath = argv[2];


    std::string extension = boost::filesystem::path(outputFilePath).extension().string();

    if(strcmp(".svg",extension.c_str())==0) iot= OneImageFlow::SVG;
    else if(strcmp(".eps",extension.c_str())==0) iot= OneImageFlow::EPS;
    else throw std::runtime_error("Output type not recognized!");

    boost::filesystem::path srcImagePath( flowImagesFolderPath );

    std::string name = srcImagePath.stem().string();
    OneImageFlow oif(srcImagePath.string(),outputFilePath,jumpStep,iot);

    return 0;
}