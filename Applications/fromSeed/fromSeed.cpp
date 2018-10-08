#include <BTools/DataReader.h>
#include "FromSeedControl.h"
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

typedef FromSeed::InputReader::InputData InputData;

void fromSeed(const InputData& inputData)
{
    typedef BinOCS::GrabCut::GrabCutApplication GCApplication;
    typedef BTools::Model::SeedSequenceInput SeedSequenceInput;

    SeedSequenceInput seedInput = BTools::DataReader::read(inputData.seedDataFilePath);

    boost::filesystem::path pFile(seedInput.imgFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("From-Seed-Selection-Highlight");
    pOutputFolder.append(pFile.filename().string());

    FromSeedControl::SelectorOutput selectorOutput;
    FromSeedControl::OptOutput optOutput(inputData.bcFlowInput,seedInput);
    selectorOutput.baseImage = cv::imread(seedInput.imgFilePath,CV_LOAD_IMAGE_COLOR);
    for(int i=0;i<seedInput.numSeed();++i)
    {
        seedInput.getSelector(selectorOutput,i);
        FromSeedControl(optOutput,
                        seedInput.imgFilePath,
                        inputData.bcFlowInput,
                        selectorOutput,
                        pOutputFolder.string() + "/ROI-" + std::to_string(i) );
    }
}

int main(int argc, char* argv[])
{
    InputData inputData;

    FromSeed::InputReader::readInput(inputData,argc,argv);
    fromSeed(inputData);
}