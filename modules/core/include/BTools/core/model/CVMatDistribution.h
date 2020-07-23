#ifndef BTools_CORE_CVMATDISTRIBUTION_H
#define BTools_CORE_CVMATDISTRIBUTION_H

#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include "BTools/core/model/GMM.h"

namespace BTools{
namespace Core{
class CVMatDistribution:public SCaBOliC::Energy::ISQ::IProbabilityDistribution<double>
{

 public:
  CVMatDistribution(const cv::Mat& img,
                    const GMM& gmm):img(img),
                                    gmm(gmm){}

  double operator()(Index row, Index col) const
  {
      double s = gmm( img.at<cv::Vec3b>(row,col)  ) + 1.0e-20;
      return s;
  }

 public:
  const cv::Mat& img;
  const GMM& gmm;

};
}
}

#endif //BTools_CORE_CVMATDISTRIBUTION_H
