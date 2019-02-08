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

void fromSeed(const FromSeed::InputReader::InputData& inputData)
{
    typedef BinOCS::GrabCut::GrabCutApplication GCApplication;
    typedef BTools::Model::SeedSequenceInput SeedSequenceInput;
    typedef BTools::Model::BCFlowInput BCFlowInput;

    SeedSequenceInput seedInput = BTools::DataReader::read(inputData.seedDataFilePath);

    boost::filesystem::path pFile(seedInput.imgFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("From-Seed-Selection-Highlight");
    pOutputFolder.append(pFile.filename().string());

    BCConfigInput bcInput(inputData.radius,
                          inputData.dtWeight,
                          inputData.sqWeight,
                          inputData.lgWeight,
                          BCConfigInput::QPBOSolverType::Probe);

    ODRConfigInput odrConfigInput(ODRConfigInput::ApplicationCenter::AC_PIXEL,
                                  ODRConfigInput::CountingMode::CM_PIXEL,
                                  ODRConfigInput::SpaceMode::Pixel,
    2,
            ODRConfigInput::LevelDefinition::LD_FartherFromCenter,
            ODRConfigInput::NeighborhoodType::FourNeighborhood,
            false,
            false);

    BCFlowInput bcFlowInput("noname",
                            bcInput,
                            odrConfigInput,
                            BCFlowInput::FlowProfile::DoubleStep,
                            inputData.iterations);


    FromSeedControl::SelectorOutput selectorOutput;
    FromSeedControl::OptOutput optOutput(bcFlowInput,seedInput);
    selectorOutput.baseImage = cv::imread(seedInput.imgFilePath,cv::ImreadModes::IMREAD_COLOR);
    for(int i=0;i<seedInput.numSeed();++i)
    {
        seedInput.getSelector(selectorOutput,i);
        FromSeedControl(optOutput,
                        seedInput.imgFilePath,
                        bcFlowInput,
                        selectorOutput,
                        pOutputFolder.string() + "/ROI-" + std::to_string(i) );
    }
}

int main(int argc, char* argv[])
{
    FromSeed::InputReader::InputData inputData;

    FromSeed::InputReader::readInput(inputData,argc,argv);
    fromSeed(inputData);
}