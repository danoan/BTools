#ifndef BTOOLS_MODEL_BCFLOWINPUT_H
#define BTOOLS_MODEL_BCFLOWINPUT_H

#include <BinOCS/core/model/input/BCApplicationInput.h>
#include <BinOCS/core/model/input/BCConfigInput.h>
#include <BinOCS/core/model/input/ODRConfigInput.h>

#include <string>


namespace BinOCS
{
    namespace Core
    {
        struct BCFlowInput
        {
            typedef BinOCS::Core::BCConfigInput BCConfigInput;
            typedef BinOCS::Core::ODRConfigInput ODRConfigInput;
            typedef BinOCS::Core::IFlowProfile::FlowProfile FlowProfile;

            BCFlowInput(const std::string& inputName,
                        const BCConfigInput& bcInput,
                        const ODRConfigInput& odrConfigInput,
                        const FlowProfile& flowProfile,
                        int maxIterations ):inputName(inputName),
                                            bcInput(bcInput),
                                            odrConfigInput(odrConfigInput),
                                            flowProfile(flowProfile),
                                            maxIterations(maxIterations){};


            BCConfigInput bcInput;
            ODRConfigInput odrConfigInput;
            FlowProfile flowProfile;
            std::string inputName;
            int maxIterations;
        };
    }
}
#endif //BTOOLS_MODEL_BCFLOWINPUT_H
