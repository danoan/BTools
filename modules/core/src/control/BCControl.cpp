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

    DigitalSet mockDS1(inputDS.domain());
    DigitalSet mockDS2(inputDS.domain());
    SolutionHint shint(mockDS1,mockDS2);

    BCControl(solution,
              bcInput,
              imageDataInput,
              odrFactory,
              flowStepConfig,
              inputDS,
              mock.begin(),
              mock.end(),
              shint);
}

BCControl::ISQInputData::OptimizationDigitalRegions BCControl::warmStart(const ISQInputData::OptimizationDigitalRegions& ODR,
                                                                         const SolutionHint& shint)
{
    DigitalSet newTrustFRG = ODR.trustFRG;
    DigitalSet newTrustBKG = ODR.trustBKG;
    DigitalSet newOptRegion = ODR.optRegion;

    for(auto it=shint.ones.begin();it!=shint.ones.end();++it)
    {
        newTrustFRG.insert(*it);
        newOptRegion.erase(*it);
    }

    for(auto it=shint.zeros.begin();it!=shint.zeros.end();++it)
    {
        newTrustBKG.insert(*it);
        newOptRegion.erase(*it);
    }

    return ISQInputData::OptimizationDigitalRegions(ODR.domain,
                                                    ODR.original,
                                                    newOptRegion,
                                                    newTrustFRG,
                                                    newTrustBKG,
                                                    ODR.applicationRegion,
                                                    ODR.toImageCoordinates);

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
