#ifndef BTools_BCAPPLICATIONINPUT_H
#define BTools_BCAPPLICATIONINPUT_H

#include <BTools/core/interface/IFlowProfile.h>

#include "BCConfigInput.h"
#include "ODRConfigInput.h"
#include "ImageDataInput.h"
#include "SolutionHint.h"

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
                               const FlowProfile& flowProfile,
                               bool showProgress=false,
                               const SolutionHint shint=SolutionHint::emptySHint): bcConfigInput(bcConfigInput),
                                                                   odrConfigInput(odrConfigInput),
                                                                   imageDataInput(imageDataInput),
                                                                   flowProfile(flowProfile),
                                                                   showProgress(showProgress)
            {}

            const FlowProfile flowProfile;
            const BCConfigInput bcConfigInput;
            const ImageDataInput imageDataInput;
            const ODRConfigInput odrConfigInput;

            bool showProgress;
            const SolutionHint shint;


        };
    }
}

#endif //BTools_BCAPPLICATIONINPUT_H
