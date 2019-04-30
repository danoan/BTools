#ifndef BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
#define BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BinOCS/core/model/input/ODRConfigInput.h"
#include "BinOCS/core/model/input/BCConfigInput.h"

#include "BinOCS/core/interface/IFlowProfile.h"


namespace BoundaryCorrection
{
    class InputReader
    {
    public:
        struct InputData
        {
            typedef BinOCS::Core::ODRConfigInput ODRConfigInput;
            typedef BinOCS::Core::IFlowProfile::FlowProfile FlowProfile;

            typedef BinOCS::Core::BCConfigInput::QPBOSolverType OptMethod;

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
