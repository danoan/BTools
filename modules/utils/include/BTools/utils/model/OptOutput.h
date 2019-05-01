#ifndef BTools_UTILS_OPTOUTPUT_H
#define BTools_UTILS_OPTOUTPUT_H

#include <opencv2/core/mat.hpp>

#include "BTools/core/model/input/BCFlowInput.h"

namespace BTools
{
    namespace Utils
    {
        struct OptOutput
        {
            typedef BTools::Core::BCFlowInput BCFlowInput;

            OptOutput(const BCFlowInput& bcFlowInput):bcFlowInput(bcFlowInput){}

            double IIElasticaValue;
            double MDCAElasticaValue;

            double optEnergyValue;
            int unlabeled;

            cv::Mat inputImage;
            cv::Mat outputImage;

            const BCFlowInput bcFlowInput;
        };
    }
}
#endif //BTools_UTILS_OPTOUTPUT_H
