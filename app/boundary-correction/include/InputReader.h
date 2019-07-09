#ifndef BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
#define BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BTools/core/model/input/ODRConfigInput.h"
#include "BTools/core/model/input/BCConfigInput.h"

#include "BTools/core/interface/IFlowProfile.h"


namespace BoundaryCorrection
{
    namespace InputReader
    {
        struct InputData
        {
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;

            typedef BTools::Core::BCConfigInput::QPBOSolverType OptMethod;

            InputData();

            int radius;
            int iterations;

            double sqWeight;
            double dtWeight;
            double lgWeight;

            std::string grabcutFile;
            OptMethod optMethod;

            bool excludeOptPointsFromAreaComputation;
            int initialDilation;

            std::string outputFolder;
            bool showIterations;
            bool showProgress;
        };

        InputData readInput(int argc,char** argv);

    }
}

#endif //BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
