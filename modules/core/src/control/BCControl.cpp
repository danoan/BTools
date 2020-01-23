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

