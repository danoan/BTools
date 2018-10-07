#ifndef BINOCS_EXPERIMENTS_SINGLEINSTANCEOUTPUT_H
#define BINOCS_EXPERIMENTS_SINGLEINSTANCEOUTPUT_H

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
#endif //BINOCS_EXPERIMENTS_SINGLEINSTANCEOUTPUT_H
