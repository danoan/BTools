#include "BTools/core/control/modelIteration.h"

namespace BTools{
namespace Core{

typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

void solveModel(Solution& solution,
                const BCInput& bcInput,
                const ODRInterface& odrFactory,
                const DigitalSet& inputDS){
  const ModelParameters& modelParameters = bcInput.modelParameters;
  const ImageData& imageData = bcInput.imageData;

  ISQInputData::OptimizationDigitalRegions ODR = odrFactory.createODR(SCaBOliC::Core::ODRModel::ApplicationMode::AM_AroundBoundary,
                                                                      inputDS,
                                                                      false);

  ISQInputData energyInput(ODR,
                           imageData.inputImage,
                           imageData.fgDistr,
                           imageData.bgDistr,
                           false,
                           false,
                           modelParameters.dataTermWeight,
                           modelParameters.sqTermWeight,
                           modelParameters.lengthTermWeight,
                           1.0,
                           1.0,
                           imageData.translation);

  ISQEnergy energy(energyInput,odrFactory.handle());
  solution.init(energy.numVars());


  energy.template solve<QPBOImproveSolver>(solution);
  updateSet(solution,
            odrFactory,
            energyInput,
            energy);
}

void updateSet(Solution& solution,
               const ODRInterface& odrFactory,
               const ISQInputData& energyInput,
               const ISQEnergy& energy)
{
  DigitalSet initialDS(energyInput.optimizationRegions.domain);
  DigitalSet tempOutDS(energyInput.optimizationRegions.domain);

  const DigitalSet& optRegion = energyInput.optimizationRegions.optRegion;
  Solution::LabelsVector labelsVector = solution.labelsVector;

  initialDS.insert(energyInput.optimizationRegions.trustFRG.begin(),
                   energyInput.optimizationRegions.trustFRG.end());

  odrFactory.handle()->solutionSet(tempOutDS,
                                   initialDS,
                                   energyInput.optimizationRegions,
                                   labelsVector.data(),
                                   energy.vm().pim);

  solution.outputDS.clear();
  solution.outputDS.insert(tempOutDS.begin(),tempOutDS.end());

}

cv::Mat createBCImage(const DigitalSet& outputDS, const ImageData& imageData){
  DigitalSet translatedBackDS( Domain( Point(0,0),
                                       Point(imageData.inputImage.cols-1,
                                             imageData.inputImage.rows-1)
  ) );

  for (auto it = outputDS.begin(); it != outputDS.end(); ++it)
  {
    Point pt = *it + imageData.translation;
    if( translatedBackDS.domain().isInside(pt) )
      translatedBackDS.insert(pt);
  }

  cv::Mat foregroundMask = cv::Mat::zeros(imageData.inputImage.size(),
                                          CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask,translatedBackDS);

  cv::Mat bcImage;
  BTools::Utils::setHighlightMask(bcImage,imageData.inputImage,foregroundMask);

  return bcImage;
}




}
}