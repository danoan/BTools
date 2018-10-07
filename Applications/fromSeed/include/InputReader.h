#ifndef BTOOLS_APPLICATION_FROMSEED_INPUTREADER_H
#define BTOOLS_APPLICATION_FROMSEED_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <BTools/model/input/BCFlowInput.h>

namespace BTools
{
    namespace Application
    {
        namespace FromSeed
        {
            class InputReader
            {
            public:
                struct InputData
                {
                    typedef BTools::Model::BCFlowInput BCFlowInput;

                    BCFlowInput bcFlowInput;
                    std::string seedDataFilePath;
                };

                static void readInput(InputData& id,
                                      int argc,
                                      char** argv);
            };
        }
    }
}

#endif //BTOOLS_APPLICATION_FROMSEED_INPUTREADER_H
