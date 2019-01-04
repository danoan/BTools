#include <InputReader.h>
#include "OneImageFlow.h"
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
    InputReader::InputData id;
    InputReader::readInput(id,argc,argv);

    Flow::BCConfigInput bcInput(id.radius,
                                0,
                                1.0,
                                0,
                                Flow::BCConfigInput::QPBOSolverType::Probe);

    FlowConfigInput fci(id.fp,id.ac,id.cm,id.sm);

    Flow::BCFlowInput bcFlowInput("Digital Shapes Flow",
                                  bcInput,
                                  fci,
                                  id.iterations);

    std::string outputFilePath = outputDir +"/flow/" + id.flowName;

    Flow flow(bcFlowInput,
              outputFilePath,
              false);

    return 0;
}

