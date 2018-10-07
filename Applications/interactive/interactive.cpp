#include "include/InteractiveControl.h"
#include "include/InputReader.h"

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

typedef Interactive::InputReader::InputData InputData;

void interactive(const InputData& inputData)
{
    boost::filesystem::path pFile(inputData.imageFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("Interactive");
    pOutputFolder.append(pFile.filename().string());

    InteractiveControl(inputData.bcFlowInput,
                       inputData.imageFilePath,
                       pOutputFolder.string());
}

int main(int argc, char* argv[])
{
    InputData inputData;
    Interactive::InputReader::readInput(inputData,argc,argv);
    interactive(inputData);
}