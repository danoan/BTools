#ifndef BINOCS_BCAPPLICATIONINPUT_H
#define BINOCS_BCAPPLICATIONINPUT_H

#include <BinOCS/core/interface/IFlowProfile.h>
#include "BCConfigInput.h"
#include "ODRConfigInput.h"
#include "ImageDataInput.h"

namespace BinOCS
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

#endif //BINOCS_BCAPPLICATIONINPUT_H
