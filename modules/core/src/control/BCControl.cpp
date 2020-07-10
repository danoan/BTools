#include "BTools/core/control/BCControl.h"

using namespace BTools::Core;

BCControl::BCControl(Solution& solution,
                     const BCInput& bcInput,
                     const ODRInterface& odrFactory,
                     const DigitalSet& inputDS)
{
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

  solve(solution,energy,energyInput,ODR,odrFactory);
}


void BCControl::solve(Solution& solution,
                      const ISQEnergy& energy,
                      const ISQInputData& energyInput,
                      const ISQInputData::OptimizationDigitalRegions& ODR,
                      const ODRInterface& odrFactory)
{
  energy.template solve<QPBOImproveSolver>(solution);
  updateSet(solution,
            odrFactory,
            energyInput,
            energy);
}

void BCControl::updateSet(Solution& solution,
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


void BCControl::printData(const Solution& solution,
                          const ISQEnergy& energy)
{
  std::cout << "Energy Value: " << solution.energyValue << std::endl;
  std::cout << "Unlabelled: " << solution.unlabeled << std::endl;

  const Solution::LabelsVector& labelsVector = solution.labelsVector;

  std::cout << "Data Energy: " << energy.dataEnergy(labelsVector) << std::endl;
  std::cout << "SQ Energy: " << energy.sqEnergy(labelsVector) << std::endl;

  std::cout << "Data Energy Not Normalized: " << energy.dataEnergyNotNormalized(labelsVector) << std::endl;
  std::cout << "SQ Energy Not Normalized: " << energy.sqEnergyNotNormalized(labelsVector) << std::endl;

  std::cout << "Data Term Real Value: " << energy.dataRealValue(labelsVector) << std::endl;
  std::cout << "SQ Term Real Value: " << energy.sqRealValue(labelsVector) << std::endl;
}
