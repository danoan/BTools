#ifndef BTools_BCAPPLICATIONINPUT_H
#define BTools_BCAPPLICATIONINPUT_H

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

            BCApplicationInput(const BCConfigInput& bcConfigInput,
                               const ImageDataInput& imageDataInput,
                               const ODRConfigInput& odrConfigInput,
                               bool showProgress=false): bcConfigInput(bcConfigInput),
                                                                   odrConfigInput(odrConfigInput),
                                                                   imageDataInput(imageDataInput),
                                                                   showProgress(showProgress)
            {}

            const BCConfigInput bcConfigInput;
            const ImageDataInput imageDataInput;
            const ODRConfigInput odrConfigInput;

            bool showProgress;


        };
    }
}

#endif //BTools_BCAPPLICATIONINPUT_H
