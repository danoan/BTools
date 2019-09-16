#ifndef BTools_UTILS_OPTOUTPUT_H
#define BTools_UTILS_OPTOUTPUT_H

#include <opencv2/core/mat.hpp>
#include "BTools/core/model/input/BCApplicationInput.h"

namespace BTools
{
    namespace Utils
    {
        struct OptOutput
        {
            typedef BTools::Core::BCApplicationInput BCApplicationInput;
            OptOutput(const BCApplicationInput& bcaInput):bcaInput(bcaInput){}

            double IIElasticaValue;
            double MDCAElasticaValue;

            double optEnergyValue;
            int unlabeled;

            cv::Mat inputImage;
            cv::Mat outputImage;

            const BCApplicationInput bcaInput;
        };
    }
}
#endif //BTools_UTILS_OPTOUTPUT_H
