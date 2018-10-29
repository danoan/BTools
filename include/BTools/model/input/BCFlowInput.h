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
            typedef BinOCS::BoundaryCorrection::FlowConfigInput FlowConfigInput;

            BCFlowInput(){};

            BCFlowInput(const std::string& inputName,
                        const BCConfigInput& bcInput,
                        const FlowConfigInput& flowConfigInput,
                        int maxIterations ):inputName(inputName),
                                            bcInput(bcInput),
                                            flowConfigInput(flowConfigInput),
                                            maxIterations(maxIterations){};


            BCConfigInput bcInput;
            FlowConfigInput flowConfigInput;
            std::string inputName;
            int maxIterations;
        };
    }
}
#endif //BTOOLS_MODEL_BCFLOWINPUT_H
