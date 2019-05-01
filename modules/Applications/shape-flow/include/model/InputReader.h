#ifndef BTOOLS_APPLICATION_FLOW_INPUTREADER_H
#define BTOOLS_APPLICATION_FLOW_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BTools/core/model/input/BCConfigInput.h"
#include "BTools/core/model/input/ODRConfigInput.h"
#include "BTools/core/interface/IFlowProfile.h"

#include "Types.h"

namespace ShapeFlow
{
    class InputReader
    {
    public:
        struct InputData
        {
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;
            typedef BTools::Core::BCConfigInput::QPBOSolverType OptMethod;

            std::string outputFolder;

            int radius;
            int iterations;
            bool useDigitalArea;


            ODRConfigInput::ApplicationCenter ac;
            ODRConfigInput::CountingMode cm;
            ODRConfigInput::SpaceMode  sm;
            ODRConfigInput::NeighborhoodType neighborhood;
            ODRConfigInput::LevelDefinition ld;
            bool optRegionInApplication;
            int levels;

            FlowProfile fp;

            double sqWeight;
            double dtWeight;
            double lgWeight;

            OptMethod optMethod;
            Shape shape;

        };

        static void readInput(InputData& id,
                              int argc,
                              char** argv);

    private:
        static void defaultValues(InputData& id);
    };
}

#endif //BTOOLS_APPLICATION_FLOW_INPUTREADER_H
