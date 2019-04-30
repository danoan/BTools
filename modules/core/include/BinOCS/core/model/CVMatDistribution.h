#ifndef BINOCS_FOREGROUNDDISTRIBUTION_H
#define BINOCS_FOREGROUNDDISTRIBUTION_H

#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include "BinOCS/core/model/GMM.h"

namespace BinOCS
{
    namespace Core
    {
        class CVMatDistribution:public SCaBOliC::Energy::ISQ::IProbabilityDistribution<double>
        {

        public:
            CVMatDistribution(const cv::Mat& img,
                              const GMM& gmm):img(img),
                                              gmm(gmm){}

            double operator()(Index row, Index col) const
            {
                return gmm( img.at<cv::Vec3b>(row,col)  );
            }

        public:
            const cv::Mat& img;
            const GMM& gmm;

        };
    }
}

#endif //BINOCS_FOREGROUNDDISTRIBUTION_H
