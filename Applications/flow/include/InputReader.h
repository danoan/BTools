#ifndef BTOOLS_APPLICATION_FLOW_INPUTREADER_H
#define BTOOLS_APPLICATION_FLOW_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <BTools/model/input/BCFlowInput.h>

#include "BinOCS/BoundaryCorrection/model/FlowConfigInput.h"

namespace BTools
{
    namespace Application
    {
        namespace Flow
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
                    bool useDigitalArea;
                    int neighborhood;
                    int levels;
                    std::string outputFolder;

                    FlowConfigInput::ApplicationCenter ac;
                    FlowConfigInput::CountingMode cm;
                    FlowConfigInput::SpaceMode  sm;
                    FlowConfigInput::FlowProfile fp;
                };

                static void readInput(InputData& id,
                                      int argc,
                                      char** argv);

            private:
                static void defaultValues(InputData& id);
            };
        }
    }
}

#endif //BTOOLS_APPLICATION_FLOW_INPUTREADER_H
