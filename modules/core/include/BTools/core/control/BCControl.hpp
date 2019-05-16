#include "BTools/core/control/BCControl.h"
using namespace BTools::Core;

template<typename TVisitorIterator>
BCControl::BCControl(Solution& solution,
                     const BCConfigInput& bcInput,
                     const ImageDataInput& imageDataInput,
                     const ODRInterface& odrFactory,
                     const IFlowStepConfig& flowStepConfig,
                     const DigitalSet& inputDS,
                     TVisitorIterator begin,
                     TVisitorIterator end,
                     const SolutionHint& shint)
{
    ISQInputData::OptimizationDigitalRegions _ODR = odrFactory.createODR(flowStepConfig.optimizationMode(),
                                                                        flowStepConfig.applicationMode(),
                                                                        inputDS,
                                                                        flowStepConfig.optInApplicationRegion());

    ISQInputData::OptimizationDigitalRegions ODR = warmStart(_ODR,shint);

    ISQInputData energyInput(ODR,
                             imageDataInput.baseImage,
                             imageDataInput.fgDistr,
                             imageDataInput.bgDistr,
                             bcInput.excludeOptPointsFromAreaComputation,
                             bcInput.penalizationMode,
                             bcInput.dataTermWeight,
                             bcInput.sqTermWeight,
                             bcInput.lengthTermWeight,
                             bcInput.penalizationWeight,
                             imageDataInput.translation);


    ISQEnergy energy(energyInput,odrFactory.handle());
    solution.init(energy.numVars());

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