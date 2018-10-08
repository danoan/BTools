#ifndef BTOOLS_MODEL_INSTANCE_H
#define BTOOLS_MODEL_INSTANCE_H

#include <BTools/model/input/BCFlowInput.h>
#include <BTools/model/input/SeedSequenceInput.h>
#include <BTools/model/output/OptOutput.h>

namespace BTools
{
    namespace Model
    {
        struct Instance
        {
            typedef BTools::Model::BCFlowInput BCFlowInput;
            typedef BTools::Model::SeedSequenceInput SeedSequenceInput;

            Instance(BCFlowInput& bcFlowInput,
                     SeedSequenceInput& seedInput):bcFlowInput(bcFlowInput),
                                                   seedInput(seedInput){}

            BCFlowInput bcFlowInput;
            SeedSequenceInput seedInput;
        };
    }
}

#endif //BTOOLS_MODEL_INSTANCE_H
