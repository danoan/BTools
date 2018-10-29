#ifndef BTOOLS_APPLICATION_ILLUSTRATION_INPUTREADER_H
#define BTOOLS_APPLICATION_ILLUSTRATION_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <BTools/model/input/BCFlowInput.h>

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            class InputReader
            {
            public:
                struct InputData
                {
                    int levelSets;
                    int radius;
                    int iterations;
                };

                static void readInput(InputData& id,
                                      int argc,
                                      char** argv);
            };
        }
    }
}

#endif //BTOOLS_APPLICATION_FROMSEED_INPUTREADER_H
