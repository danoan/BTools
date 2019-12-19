#ifndef BTOOLS_INPUTDATA_H
#define BTOOLS_INPUTDATA_H


#include <unistd.h>

#include "BTools/core/model/input/BCConfigInput.h"
#include "BTools/core/model/input/ODRConfigInput.h"

#include "Types.h"

namespace BTools
{
    namespace Reader
    {
        namespace DCFReader
        {
            struct InputData
            {
                typedef BTools::Core::ODRConfigInput ODRConfigInput;
                typedef BTools::Core::BCConfigInput::QPBOSolverType OptMethod;

                typedef BTools::Core::ODRConfigInput::ApplicationMode ApplicationMode;

                InputData(){};

                int radius;
                int iterations;

                ODRConfigInput::NeighborhoodType neighborhood;
                ODRConfigInput::LevelDefinition ld;

                bool optRegionInApplication;
                double levels;
                double optBand;

                double sqWeight;
                double dtWeight;
                double lgWeight;

                std::string pixelMaskFilepath;

                OptMethod optMethod;
                Shape shape;
                double gridStep;

                bool excludeOptPointsFromAreaComputation;
                bool uniformPerimeter;

                double innerBallCoeff,outerBallCoeff;

                ApplicationMode am;

            };
        }
    }
}

#endif //BTOOLS_INPUTDATA_H
