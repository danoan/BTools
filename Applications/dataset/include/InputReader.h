#ifndef BTOOLS_APPLICATION_DATASET_INPUTREADER_H
#define BTOOLS_APPLICATION_DATASET_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <BTools/model/input/BCFlowInput.h>

namespace BTools
{
    namespace Application
    {
        namespace Dataset
        {
            class InputReader
            {
            public:
                struct InputData
                {
                    typedef BinOCS::BoundaryCorrection::ODRConfigInput ODRConfigInput;
                    typedef BinOCS::BoundaryCorrection::IFlowProfile::FlowProfile FlowProfile;

                    typedef BinOCS::BoundaryCorrection::BCConfigInput::QPBOSolverType OptMethod;

                    int radius;
                    int iterations;

                    double sqWeight;
                    double dtWeight;
                    double lgWeight;

                    std::string datasetPath;
                    OptMethod optMethod;
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

#endif //BTOOLS_APPLICATION_DATASET_INPUTREADER_H
