#ifndef BTools_BCAPPLICATIONINPUT_H
#define BTools_BCAPPLICATIONINPUT_H

#include <BTools/core/interface/IFlowProfile.h>
#include "BCConfigInput.h"
#include "ODRConfigInput.h"
#include "ImageDataInput.h"

namespace BTools
{
    namespace Core
    {
        struct BCApplicationInput
        {
        public:
            typedef IFlowProfile::FlowProfile FlowProfile;
        public:

            BCApplicationInput(const BCConfigInput& bcConfigInput,
                               const ImageDataInput& imageDataInput,
                               const ODRConfigInput& odrConfigInput,
                               const FlowProfile& flowProfile): bcConfigInput(bcConfigInput),
                                                                odrConfigInput(odrConfigInput),
                                                                imageDataInput(imageDataInput),
                                                                flowProfile(flowProfile)
            {}

            const FlowProfile flowProfile;

            const BCConfigInput bcConfigInput;
            const ImageDataInput imageDataInput;
            const ODRConfigInput odrConfigInput;

        };
    }
}

#endif //BTools_BCAPPLICATIONINPUT_H
