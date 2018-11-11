#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include "OneImageFlow.h"

using namespace BTools::Application::Flow;

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        std::cerr << "Usage " << argv[0] << " Flow_Images_Folder_Path [Jump_Step]" <<std::endl;
        exit(1);
    }

    int jumpStep = 2;
    if(argc==3) jumpStep = atoi(argv[2]);

    boost::filesystem::path srcImagePath = argv[1];
    boost::filesystem::directory_iterator di(srcImagePath);
    while(di!=boost::filesystem::directory_iterator())
    {
        if( boost::filesystem::is_directory(*di) )
        {
            std::string name = di->path().stem().string();
            std::string outputImagePath = srcImagePath.string() + "/" + name + ".eps";
            OneImageFlow oif(di->path().string(),outputImagePath,jumpStep   );
        }
        ++di;
    }

    return 0;
}