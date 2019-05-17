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
                             bcInput.repeatedImprovement,
                             bcInput.dataTermWeight,
                             bcInput.sqTermWeight,
                             bcInput.lengthTermWeight,
                             bcInput.penalizationWeight,
                             imageDataInput.translation);

    ISQEnergy energy(energyInput,odrFactory.handle());
    solution.init(energy.numVars());


    ISQInputData::OptimizationDigitalRegions *ptPreviousODR, *ptODR;
    ISQInputData *ptPreviousEnergyInput, *ptEnergyInput;

    if(bcInput.repeatedImprovement)
    {
        ptPreviousODR = &ODR;
        ptPreviousEnergyInput = &energyInput;

        int rep=0;
        while(rep<20)
        {
            solve(solution,bcInput,energy,*ptPreviousEnergyInput,*ptPreviousODR,odrFactory,flowStepConfig,begin,end);

            ptODR = new ISQInputData::OptimizationDigitalRegions( updateODR(flowStepConfig,odrFactory,*ptPreviousODR,solution) );
            ptEnergyInput = new ISQInputData( updateEnergyInput(*ptODR,*ptPreviousEnergyInput) );

            reweight(energy,*ptEnergyInput);

            if(rep>0)
            {
                delete ptPreviousODR;
                delete ptPreviousEnergyInput;
            }

            ptPreviousODR = ptODR;
            ptPreviousEnergyInput = ptEnergyInput;

            rep++;
        }

        delete ptPreviousODR;
        delete ptPreviousEnergyInput;

    }else
    {
        solve(solution,bcInput,energy,energyInput,ODR,odrFactory,flowStepConfig,begin,end);
    }


}