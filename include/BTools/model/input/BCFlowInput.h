#ifndef BTOOLS_MODEL_BCFLOWINPUT_H
#define BTOOLS_MODEL_BCFLOWINPUT_H

#include <BinOCS/BoundaryCorrection/model/BCApplicationInput.h>
#include <string>


namespace BTools
{
    namespace Model
    {
        struct BCFlowInput
        {
            typedef BinOCS::BoundaryCorrection::BCConfigInput BCConfigInput;

            BCFlowInput(){};

            BCFlowInput(const std::string& inputName,
                        const BCConfigInput& bcInput,
                        int maxIterations ):inputName(inputName),
                                            bcInput(bcInput),
                                            maxIterations(maxIterations){};


            BCConfigInput bcInput;
            std::string inputName;
            int maxIterations;
        };
    }
}
#endif //BTOOLS_MODEL_BCFLOWINPUT_H
