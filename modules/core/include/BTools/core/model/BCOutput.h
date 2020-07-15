#ifndef BTools_CORE_BCOUTPUT_H
#define BTools_CORE_BCOUTPUT_H

#include <opencv2/core/mat.hpp>

#include <SCaBOliC/Energy/model/Solution.h>
#include <DIPaCUS/base/Representation.h>

#include "BTools/core/model/input/BCInput.h"

namespace BTools{
namespace Core{
class BCOutput{
 public:
  typedef SCaBOliC::Energy::Solution EnergySolution;
  typedef DGtal::Z2i::Domain Domain;
  typedef DGtal::Z2i::Point Point;

 public:
  BCOutput(const BCInput& bcInput)
      :bcInput(bcInput),
       grabcutImage(bcInput.imageData.grabcutImage.clone()),
       energySolution(bcInput.imageData.inputDomain)
  {}

  BCOutput& operator=(const BCOutput& other)
  {
    this->energySolution = other.energySolution;
    this->grabcutImage = other.grabcutImage;
    this->bcImageOutput = other.bcImageOutput;

    return *this;
  }

  BCOutput(const BCInput& bcInput,
           const EnergySolution& energySolution,
           const cv::Mat& bcImageOutput)
      :bcInput(bcInput),
       grabcutImage(bcInput.imageData.grabcutImage.clone()),
       energySolution(bcInput.imageData.inputDomain),
       bcImageOutput(bcImageOutput){}

 public:
  const BCInput& bcInput;

  EnergySolution energySolution;

  cv::Mat grabcutImage;
  cv::Mat bcImageOutput;

  double IIElasticaValue;
  double MDCAElasticaValue;
};
}
}

#endif //BTools_CORE_BCOUTPUT_H
