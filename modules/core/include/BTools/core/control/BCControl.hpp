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
                     TVisitorIterator end)
{
    ISQInputData::OptimizationDigitalRegions ODR = odrFactory.createODR(flowStepConfig.optimizationMode(),
                                                                        flowStepConfig.applicationMode(),
                                                                        bcInput.radius,
                                                                        inputDS,
                                                                        flowStepConfig.optInApplicationRegion());

    ISQInputData energyInput(ODR,
                             imageDataInput.baseImage,
                             bcInput.radius,
                             imageDataInput.fgDistr,
                             imageDataInput.bgDistr,
                             bcInput.dataTermWeight,
                             bcInput.sqTermWeight,
                             bcInput.lengthTermWeight,
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