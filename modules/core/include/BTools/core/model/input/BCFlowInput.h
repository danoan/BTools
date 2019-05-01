#ifndef BTOOLS_MODEL_BCFLOWINPUT_H
#define BTOOLS_MODEL_BCFLOWINPUT_H

#include <BTools/core/model/input/BCApplicationInput.h>
#include <BTools/core/model/input/BCConfigInput.h>
#include <BTools/core/model/input/ODRConfigInput.h>

#include <string>


namespace BTools
{
    namespace Core
    {
        struct BCFlowInput
        {
            typedef BTools::Core::BCConfigInput BCConfigInput;
            typedef BTools::Core::ODRConfigInput ODRConfigInput;
            typedef BTools::Core::IFlowProfile::FlowProfile FlowProfile;

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
