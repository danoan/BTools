#ifndef BTools_UTILS_OPTOUTPUT_H
#define BTools_UTILS_OPTOUTPUT_H

#include <opencv2/core/mat.hpp>
#include "BTools/core/model/input/BCInput.h"

namespace BTools
{
    namespace Utils
    {
        struct OptOutput
        {
            typedef BTools::Core::BCInput BCInput;
            OptOutput(const BCInput& bcaInput):bcInput(bcInput){}

            double IIElasticaValue;
            double MDCAElasticaValue;

            double optEnergyValue;
            int unlabeled;

            cv::Mat inputImage;
            cv::Mat outputImage;

            const BCInput bcInput;
        };
    }
}
#endif //BTools_UTILS_OPTOUTPUT_H
