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

int main()
{
    AroundBoundaryReasoning abr(outputDir + "/illustration/ab-reasoning");

    Flow::BCConfigInput bcInput(3,
                                0,
                                1.0,
                                0,
                                Flow::BCConfigInput::QPBOSolverType::Probe);

    Flow::BCFlowInput bcFlowInput("Digital Shapes Flow",
                                  bcInput,
                                  20);

    Flow flow(bcFlowInput,
              outputDir +"/illustration/flow-b3-r3",
              false);

    boost::filesystem::path srcImagePath = outputDir +"/illustration/flow-b3-r3";
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

