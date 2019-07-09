#include "BTools/core/control/BCControl.h"
using namespace BTools::Core;

template<typename TVisitorIterator>
void BCControl::solve(Solution& solution,
                      const BCConfigInput& bcInput,
                      const ISQEnergy& energy,
                      const ISQInputData& energyInput,
                      const ISQInputData::OptimizationDigitalRegions& ODR,
                      const ODRInterface& odrFactory,
                      const IFlowStepConfig& flowStepConfig,
                      TVisitorIterator begin,
                      TVisitorIterator end)
{
    flowStepConfig.initialSolution(solution.labelsVector);

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
              flowStepConfig,
              energyInput,
              energy);

    for(TVisitorIterator it=begin;it!=end;++it)
    {
        (*it)->visit(energy.energy.od,energy.vm(),ODR);
    }
}

template<typename TVisitorIterator>
BCControl::BCControl(Solution& solution,
                     const BCConfigInput& bcInput,
                     const ImageDataInput& imageDataInput,
                     const ODRInterface& odrFactory,
                     const IFlowStepConfig& flowStepConfig,
                     const DigitalSet& inputDS,
                     TVisitorIterator begin,
                     TVisitorIterator end)
{
    ISQInputData::OptimizationDigitalRegions ODR = odrFactory.createODR(flowStepConfig.optimizationMode(),
                                                                        flowStepConfig.applicationMode(),
                                                                        inputDS,
                                                                        flowStepConfig.optInApplicationRegion());

    ISQInputData energyInput(ODR,
                             imageDataInput.baseImage,
                             imageDataInput.fgDistr,
                             imageDataInput.bgDistr,
                             bcInput.excludeOptPointsFromAreaComputation,
                             flowStepConfig.shrinkingMode(),
                             bcInput.dataTermWeight,
                             bcInput.sqTermWeight,
                             bcInput.lengthTermWeight,
                             imageDataInput.translation);

    ISQEnergy energy(energyInput,odrFactory.handle());
    solution.init(energy.numVars());

    solve(solution,bcInput,energy,energyInput,ODR,odrFactory,flowStepConfig,begin,end);

}