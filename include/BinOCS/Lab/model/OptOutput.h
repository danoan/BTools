#ifndef BINOCS_EXPERIMENTS_SINGLEINSTANCEOUTPUT_H
#define BINOCS_EXPERIMENTS_SINGLEINSTANCEOUTPUT_H

#include <opencv2/core/mat.hpp>

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            struct OptOutput
            {
                double IIElasticaValue;
                double MDCAElasticaValue;

                double optEnergyValue;
                int unlabeled;

                cv::Mat inputImage;
                cv::Mat outputImage;
            };
        }
    }
}
#endif //BINOCS_EXPERIMENTS_SINGLEINSTANCEOUTPUT_H
