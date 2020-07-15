#ifndef BTools_CORE_BCINPUT_H
#define BTools_CORE_BCINPUT_H

#include "ModelParameters.h"
#include "ImageData.h"

namespace BTools{
namespace Core{
struct BCInput{
  BCInput(const ModelParameters& modelParameters,
          const ImageData& imageData,
          int maxIterations = 10,
          bool displayEachIteration=false,
          bool showProgress=false): modelParameters(modelParameters),
                                    imageData(imageData),
                                    maxIterations(maxIterations),
                                    displayEachIteration(displayEachIteration),
                                    showProgress(showProgress)
  {}

  const ModelParameters& modelParameters;
  const ImageData& imageData;

  int maxIterations;
  bool displayEachIteration;
  bool showProgress;

};
}
}

#endif //BTools_CORE_BCINPUT_H
