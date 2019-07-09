#include "BTools/core/control/BCControl.h"

using namespace BTools::Core;

BCControl::BCControl(Solution& solution,
                     const BCConfigInput& bcInput,
                     const ImageDataInput& imageDataInput,
                     const ODRInterface& odrFactory,
                     const IFlowStepConfig& flowStepConfig,
                     const DigitalSet& inputDS)
{
    std::vector< IBCControlVisitor* > mock;

    BCControl(solution,
              bcInput,
              imageDataInput,
              odrFactory,
              flowStepConfig,
              inputDS,
              mock.begin(),
              mock.end());
}


void BCControl::updateSet(Solution& solution,
                          const ODRInterface& odrFactory,
                          const IFlowStepConfig& flowStepConfig,
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
                                     flowStepConfig.optimizationMode(),
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
