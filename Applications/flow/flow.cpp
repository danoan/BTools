#include <InputReader.h>
#include "OneImageFlow.h"
#include "FlowControl.h"

namespace BTools
{
    namespace Application
    {
        std::string projectDir = PROJECT_DIR;
        std::string outputDir = projectDir + "/output";
    }
}

using namespace BTools::Application::Flow;
using namespace BTools::Application;

int main(int argc, char* argv[])
{
    InputReader::InputData id;
    InputReader::readInput(id,argc,argv);

    FlowControl::BCConfigInput bcInput(id.radius,
                                       0,
                                       1.0,
                                       0,
                                       FlowControl::BCConfigInput::QPBOSolverType::Probe);

    FlowConfigInput fci(id.fp,id.ac,id.cm,id.sm);

    FlowControl::BCFlowInput bcFlowInput("Digital Shapes Flow",
                                         bcInput,
                                         fci,
                                         id.iterations);

    std::string outputFilePath = outputDir +"/flow-ab1/" + id.flowName;

    FlowControl flow(bcFlowInput,
                     outputFilePath,
                     false);

    return 0;
}

