#ifndef BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
#define BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BTools/core/model/input/ODRConfigInput.h"
#include "BTools/core/model/input/BCConfigInput.h"

#include "BTools/core/interface/IFlowProfile.h"


namespace BoundaryCorrection
{
    class InputReader
    {
    public:
        struct InputData
        {
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;

            typedef BTools::Core::BCConfigInput::QPBOSolverType OptMethod;

            int radius;
            int iterations;

            double sqWeight;
            double dtWeight;
            double lgWeight;

            std::string grabcutFile;
            OptMethod optMethod;

            std::string outputFolder;
            bool showIterations;
        };

        static void readInput(InputData& id,
                              int argc,
                              char** argv);

    private:
        static void defaultValues(InputData& id);
    };
}

#endif //BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
