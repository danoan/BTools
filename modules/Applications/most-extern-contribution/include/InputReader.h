#ifndef BTOOLS_APPLICATION_MOSTEXTERN_INPUTREADER_H
#define BTOOLS_APPLICATION_MOSTEXTERN_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BTools/core/model/input/BCConfigInput.h"
#include "BTools/core/model/input/ODRConfigInput.h"
#include "BTools/core/interface/IFlowProfile.h"

#include "Types.h"

namespace MostExternContribution
{
    namespace InputReader
    {

        struct InputData
        {
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;
            typedef BTools::Core::BCConfigInput::QPBOSolverType OptMethod;

            InputData();

            std::string outputFolder;

            int radius;
            int iterations;

            ODRConfigInput::StructuringElementType seType;

            Shape shape;
            double gridStep;

        };

        InputData readInput(int argc,
                            char** argv);

    };
}

#endif //BTOOLS_APPLICATION_FLOW_INPUTREADER_H
