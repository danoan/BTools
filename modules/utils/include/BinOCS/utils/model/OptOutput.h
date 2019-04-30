#ifndef BINOCS_UTILS_OPTOUTPUT_H
#define BINOCS_UTILS_OPTOUTPUT_H

#include <opencv2/core/mat.hpp>

#include "BinOCS/core/model/input/BCFlowInput.h"

namespace BinOCS
{
    namespace Utils
    {
        struct OptOutput
        {
            typedef BinOCS::Core::BCFlowInput BCFlowInput;

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
#endif //BINOCS_UTILS_OPTOUTPUT_H
