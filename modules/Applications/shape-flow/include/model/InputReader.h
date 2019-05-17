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
    namespace InputReader
    {
        struct InputData
        {
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;
            typedef BTools::Core::BCConfigInput::QPBOSolverType OptMethod;
            typedef ShapeFlow::Shape Shape;
            typedef BTools::Core::BCConfigInput::PenalizationMode PenalizationMode;

            InputData();

            std::string outputFolder;

            int radius;
            int iterations;

            ODRConfigInput::ApplicationCenter ac;
            ODRConfigInput::CountingMode cm;
            ODRConfigInput::SpaceMode  sm;
            ODRConfigInput::NeighborhoodType neighborhood;
            ODRConfigInput::LevelDefinition ld;
            ODRConfigInput::StructuringElementType seType;

            bool optRegionInApplication;
            int levels;

            FlowProfile fp;

            double sqWeight;
            double dtWeight;
            double lgWeight;
            double penalizationWeight;

            OptMethod optMethod;
            Shape shape;
            double gridStep;

            bool excludeOptPointsFromAreaComputation;
            PenalizationMode penalizationMode;
            
            bool repeatedImprovement;

        };

        InputData readInput(int argc,
                            char** argv);

    }
}

#endif //BTOOLS_APPLICATION_FLOW_INPUTREADER_H
