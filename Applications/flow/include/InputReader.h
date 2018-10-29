#ifndef BTOOLS_APPLICATION_ILLUSTRATION_INPUTREADER_H
#define BTOOLS_APPLICATION_ILLUSTRATION_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <BTools/model/input/BCFlowInput.h>

#include "BinOCS/BoundaryCorrection/model/FlowConfigInput.h"

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            class InputReader
            {
            public:
                struct InputData
                {
                    typedef BinOCS::BoundaryCorrection::FlowConfigInput FlowConfigInput;

                    std::string flowName;
                    int radius;
                    int iterations;

                    FlowConfigInput::ApplicationCenter ac;
                    FlowConfigInput::CountingMode cm;
                    FlowConfigInput::SpaceMode  sm;
                    FlowConfigInput::FlowProfile fp;
                };

                static void readInput(InputData& id,
                                      int argc,
                                      char** argv);
            };
        }
    }
}

#endif //BTOOLS_APPLICATION_FROMSEED_INPUTREADER_H
