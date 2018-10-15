#include <InputReader.h>
#include "OneImageFlow.h"
#include "AroundBoundaryReasoning.h"
#include "Flow.h"

namespace BTools
{
    namespace Application
    {
        std::string projectDir = PROJECT_DIR;
        std::string outputDir = projectDir + "/output";
    }
}

using namespace BTools::Application::Illustration;
using namespace BTools::Application;

int main(int argc, char* argv[])
{
    //AroundBoundaryReasoning abr(outputDir + "/illustration/ab-reasoning");

    InputReader::InputData id;
    InputReader::readInput(id,argc,argv);

    Flow::BCConfigInput bcInput(id.radius,
                                0,
                                1.0,
                                0,
                                Flow::BCConfigInput::QPBOSolverType::Probe);

    Flow::BCFlowInput bcFlowInput("Digital Shapes Flow",
                                  bcInput,
                                  id.iterations);

    std::string outputFilePath = outputDir +"/illustration/flow-b" + std::to_string(id.radius);

    Flow flow(bcFlowInput,
              outputFilePath,
              false);

    boost::filesystem::path srcImagePath = outputFilePath;
    boost::filesystem::directory_iterator di(srcImagePath);
    while(di!=boost::filesystem::directory_iterator())
    {
        if( boost::filesystem::is_directory(*di) )
        {
            std::string name = di->path().stem().string();
            std::string outputImagePath = srcImagePath.string() + "/" + name + ".eps";
            OneImageFlow oif(di->path().string(),outputImagePath,2);
        }
        ++di;
    }

    return 0;
}

