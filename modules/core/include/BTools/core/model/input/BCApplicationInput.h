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
                               const std::string& inputName,
                               bool showProgress=false): bcConfigInput(bcConfigInput),
                                                                   odrConfigInput(odrConfigInput),
                                                                   imageDataInput(imageDataInput),
                                                                   inputName(inputName),
                                                                   showProgress(showProgress)
            {}

            const BCConfigInput bcConfigInput;
            const ImageDataInput imageDataInput;
            const ODRConfigInput odrConfigInput;

            std::string inputName;
            bool showProgress;


        };
    }
}

#endif //BTools_BCAPPLICATIONINPUT_H
