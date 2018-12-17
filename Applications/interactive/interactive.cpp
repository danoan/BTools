#include "InteractiveControl.h"
#include "InputReader.h"

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


void interactive(const Interactive::InputReader::InputData& inputData)
{
    typedef BTools::Model::BCFlowInput BCFlowInput;

    boost::filesystem::path pFile(inputData.imageFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("Interactive");
    pOutputFolder.append(pFile.filename().string());

    BCConfigInput bcInput(inputData.radius,
                          inputData.dtWeight,
                          inputData.sqWeight,
                          inputData.lgWeight,
                          BCConfigInput::QPBOSolverType::Probe);

    ODRConfigInput odrConfigInput(inputData.ac,
                                  inputData.am,
                                  inputData.cm,
                                  inputData.sm,
                                  inputData.levels,
                                  inputData.neighborhood);

    BCFlowInput bcFlowInput("noname",
                            bcInput,
                            odrConfigInput,
                            inputData.fp,
                            inputData.iterations);

    InteractiveControl(bcFlowInput,
                       inputData.imageFilePath,
                       pOutputFolder.string());
}

int main(int argc, char* argv[])
{
    Interactive::InputReader::InputData inputData;
    Interactive::InputReader::readInput(inputData,argc,argv);
    interactive(inputData);
}