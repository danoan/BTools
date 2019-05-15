#ifndef BTOOLS_REGIONSOFINTEREST_INPUTREADER_H
#define BTOOLS_REGIONSOFINTEREST_INPUTREADER_H

#include <unistd.h>

#include <BTools/core/model/input/ODRConfigInput.h>
#include <BTools/core/interface/IFlowProfile.h>
#include <SCaBOliC/Core/ODRModel.h>

#include "Types.h"

namespace RegionsOfInterest
{
    namespace InputReader
    {
        struct InputData
        {
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;
            typedef SCaBOliC::Core::ODRModel ODRModel;

            InputData();

            std::string outputFilepath;

            double radius;

            ODRConfigInput::ApplicationCenter ac;
            ODRConfigInput::CountingMode cm;
            ODRConfigInput::SpaceMode  sm;
            ODRConfigInput::NeighborhoodType neighborhood;
            ODRConfigInput::LevelDefinition ld;
            ODRConfigInput::StructuringElementType  seType;

            ODRModel::OptimizationMode  om;
            ODRModel::ApplicationMode  am;

            FlowProfile fp;

            bool optRegionInApplication;
            int levels;

            Shape shape;
            double gridStep;
        };

        void usage(char* argv[]);
        InputData readInput(int argc,char** argv);
    }
}

#endif //BTOOLS_REGIONSOFINTEREST_INPUTREADER_H
