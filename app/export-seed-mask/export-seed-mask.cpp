#include <iostream>

#include <unistd.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "../../modules/io/seed/include/BTools/io/seed/GrabCutObject.h"

using namespace BTools::Utils::GrabCutIO;

void usage(char* argv[])
{
    std::cout << "Usage: " << argv[0] << "GRABCUT_OBJECT_FILE OUTPUT_PATH \n";
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        usage(argv);
        exit(1);
    }

    std::string grabcutObjectPath = argv[1];
    std::string outputPath = argv[2];

    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());

    GrabCutObject gco = read(grabcutObjectPath);
    cv::imwrite(outputPath,gco.seeds);

    return 0;
}