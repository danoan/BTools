#include "BTools/core/control/BCControl.h"

using namespace BTools::Core;

BCControl::BCControl(Solution& solution,
                     const BCApplicationInput& bcaInput,
                     const ODRInterface& odrFactory,
                     const DigitalSet& inputDS)
{
    const BCConfigInput& bcInput = bcaInput.bcConfigInput;
    const ODRConfigInput& odrConfigInput = bcaInput.odrConfigInput;
    const ImageDataInput& imageDataInput = bcaInput.imageDataInput;

    ISQInputData::OptimizationDigitalRegions ODR = odrFactory.createODR(odrConfigInput.applicationMode,
                                                                        inputDS,
                                                                        odrConfigInput.optInApplicationRegion);

    ISQInputData energyInput(ODR,
                             imageDataInput.baseImage,
                             imageDataInput.fgDistr,
                             imageDataInput.bgDistr,
                             bcInput.excludeOptPointsFromAreaComputation,
                             bcInput.dataTermWeight,
                             bcInput.sqTermWeight,
                             bcInput.lengthTermWeight,
                             imageDataInput.translation);

    ISQEnergy energy(energyInput,odrFactory.handle());
    solution.init(energy.numVars());

    solve(solution,bcInput,energy,energyInput,ODR,odrFactory);
}


void BCControl::solve(Solution& solution,
                      const BCConfigInput& bcInput,
                      const ISQEnergy& energy,
                      const ISQInputData& energyInput,
                      const ISQInputData::OptimizationDigitalRegions& ODR,
                      const ODRInterface& odrFactory)
{
    switch(bcInput.solverType)
    {
        case QPBOSolverType::Simple:
            energy.template solve<QPBOSimpleSolver>(solution);
            break;
        case QPBOSolverType::Improve:
            energy.template solve<QPBOImproveSolver>(solution);
            break;
        case QPBOSolverType::Probe:
            energy.template solve<QPBOProbeSolver>(solution);
            break;
    }

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
