#ifndef BTOOLS_MODEL_OPTOUTPUT_H
#define BTOOLS_MODEL_OPTOUTPUT_H

#include <opencv2/core/mat.hpp>
#include <BTools/model/input/SeedSequenceInput.h>

namespace BTools
{
    namespace Model
    {
        struct OptOutput
        {
            typedef BTools::Model::BCFlowInput BCFlowInput;
            typedef BTools::Model::SeedSequenceInput SeedSequenceInput;

            OptOutput(const BCFlowInput& bcFlowInput,
                      const SeedSequenceInput& seedInput):bcFlowInput(bcFlowInput),
                                                          seedInput(seedInput){}

            double IIElasticaValue;
            double MDCAElasticaValue;

            double optEnergyValue;
            int unlabeled;

            cv::Mat inputImage;
            cv::Mat outputImage;

            const BCFlowInput bcFlowInput;
            const SeedSequenceInput seedInput;
        };
    }
}
#endif //BTOOLS_MODEL_OPTOUTPUT_H
