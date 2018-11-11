#ifndef BTOOLS_MODEL_BCFLOWINPUT_H
#define BTOOLS_MODEL_BCFLOWINPUT_H

#include <BinOCS/BoundaryCorrection/model/input/BCApplicationInput.h>
#include <BinOCS/BoundaryCorrection/model/input/BCConfigInput.h>
#include <BinOCS/BoundaryCorrection/model/input/ODRConfigInput.h>

#include <string>


namespace BTools
{
    namespace Model
    {
        struct BCFlowInput
        {
            typedef BinOCS::BoundaryCorrection::BCConfigInput BCConfigInput;
            typedef BinOCS::BoundaryCorrection::ODRConfigInput ODRConfigInput;
            typedef BinOCS::BoundaryCorrection::IFlowProfile::FlowProfile FlowProfile;

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
