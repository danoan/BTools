#include "MultipleSelectorControl.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <InputReader.h>

namespace BTools
{
    namespace Application
    {
        std::string projectDir = PROJECT_DIR;
        std::string imageDir = projectDir + "/images";
        std::string outputDir = projectDir + "/output";
    }
}


using namespace BTools::Application;

void multipleSelection(const MultipleSelector::InputReader::InputData& inputData)
{
    boost::filesystem::path datasetPath(inputData.datasetPath);
    boost::filesystem::directory_iterator di(datasetPath);

    std::string outputFilepath;
    std::string windowName = "Mask Selector";
    std::string outputDataDir = outputDir + "/multipleSelector";
    boost::filesystem::create_directories(outputDataDir);
    while(di!=boost::filesystem::directory_iterator())
    {
        if(di->path().extension()==".jpg")
        {
            outputFilepath = outputDataDir + "/" + di->path().stem().string() + ".txt";
            MultipleSelectorControl(di->path().string(),
                                    windowName,
                                    outputFilepath);
            cv::destroyWindow(windowName);
        }
        ++di;
    }
}

int main(int argc, char* argv[])
{
    MultipleSelector::InputReader::InputData inputData;
    MultipleSelector::InputReader::readInput(inputData,
                                             argc,
                                             argv);

    multipleSelection(inputData);

    return 0;
}