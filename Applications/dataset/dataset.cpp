#include "DatasetControl.h"
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

template<typename TInstanceProfile>
void dataset(const std::string& prefix, const Dataset::InputReader::InputData& inputData)
{
    typedef BTools::Model::BCFlowInput BCFlowInput;
    std::string outputFolder = outputDir + "/Dataset-" + prefix +
                               std::to_string(inputData.iterations) + "it";

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

    BCFlowInput bcFlowInput("Noname",
                            bcInput,
                            odrConfigInput,
                            BCFlowInput::FlowProfile::DoubleStep,
                            inputData.iterations);
    
    DatasetControl::runFlowOnDataset<TInstanceProfile>(inputData.datasetPath,
                                                       bcFlowInput,
                                                       outputFolder);
}

int main(int argc, char* argv[])
{
    typedef BTools::Model::CurvatureProfile CurvatureProfile;
    typedef BTools::Model::DataTermProfile DataTermProfile;
    
    Dataset::InputReader::InputData inputData;
    Dataset::InputReader::readInput(inputData,argc,argv);
    

    dataset<CurvatureProfile>("Curvature-",inputData);
    dataset<DataTermProfile>("Data-",inputData);
}