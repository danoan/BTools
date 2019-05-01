#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "OneImageFlow.h"

using namespace SummaryFlow;

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cerr << "Usage " << argv[0] << " Flow_Images_Folder_Path Output_Name [Jump_Step]" <<std::endl;
        exit(1);
    }

    int jumpStep = 2;
    if(argc==4) jumpStep = atoi(argv[3]);

    std::string flowImagesFolderPath = argv[1];
    std::string outputName = argv[2];
    boost::filesystem::path srcImagePath( flowImagesFolderPath );

    std::string name = srcImagePath.stem().string();
    std::string outputImagePath = srcImagePath.string() + "/" + outputName + ".eps";
    OneImageFlow oif(srcImagePath.string(),outputImagePath,jumpStep);

    return 0;
}