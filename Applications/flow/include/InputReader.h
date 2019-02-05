#ifndef BTOOLS_APPLICATION_FLOW_INPUTREADER_H
#define BTOOLS_APPLICATION_FLOW_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <BTools/model/input/BCFlowInput.h>
#include <BinOCS/BoundaryCorrection/model/input/BCConfigInput.h>


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
                    typedef BinOCS::BoundaryCorrection::ODRConfigInput ODRConfigInput;
                    typedef BinOCS::BoundaryCorrection::IFlowProfile::FlowProfile FlowProfile;

                    typedef BinOCS::BoundaryCorrection::BCConfigInput::QPBOSolverType OptMethod;

                    std::string flowName;
                    std::string outputFolder;

                    int radius;
                    int iterations;
                    bool useDigitalArea;


                    ODRConfigInput::ApplicationCenter ac;
                    ODRConfigInput::CountingMode cm;
                    ODRConfigInput::SpaceMode  sm;
                    ODRConfigInput::NeighborhoodType neighborhood;
                    ODRConfigInput::LevelDefinition ld;
                    int levels;

                    FlowProfile fp;

                    double sqWeight;
                    double dtWeight;
                    double lgWeight;

                    OptMethod optMethod;

                    bool optRegionInApplication;
                    bool invertFrgBkg;
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
