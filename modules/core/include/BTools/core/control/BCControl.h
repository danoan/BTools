#ifndef BTools_BOUNDARYCORRECTION_BCCONTROL_H
#define BTools_BOUNDARYCORRECTION_BCCONTROL_H

#include <SCaBOliC/Energy/model/Solution.h>
#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include <SCaBOliC/Optimization/solver/QPBOSolverType.h>
#include "SCaBOliC/Core/interface/ODRInterface.h"

#include "BTools/core/interface/IFlowStepConfig.h"
#include "BTools/core/interface/IBCControlVisitor.h"
#include "BTools/core/model/input/ImageDataInput.h"
#include "BTools/core/model/input/BCConfigInput.h"
#include "BTools/core/model/input/SolutionHint.h"

namespace BTools
{
    namespace Core
    {
        class BCControl
        {
        private:
            typedef SCaBOliC::Energy::ISQ::InputData ISQInputData;
            typedef SCaBOliC::Energy::ISQEnergy ISQEnergy;
            typedef SCaBOliC::Core::ODRInterface ODRInterface;

            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef ISQInputData::cvColorImage cvColorImage;

            typedef SCaBOliC::Optimization::QPBOSolverType QPBOSolverType;

        public:
            typedef SCaBOliC::Energy::Solution Solution;

        public:
            BCControl(Solution& solution,
                      const BCConfigInput& bcInput,
                      const ImageDataInput& imageDataInput,
                      const ODRInterface& odrFactory,
                      const IFlowStepConfig& flowStepConfig,
                      const DigitalSet& inputDS);

            template<typename TVisitorIterator>
            BCControl(Solution& solution,
                      const BCConfigInput& bcInput,
                      const ImageDataInput& imageDataInput,
                      const ODRInterface& odrFactory,
                      const IFlowStepConfig& flowStepConfig,
                      const DigitalSet& inputDS,
                      TVisitorIterator begin,
                      TVisitorIterator end,
                      const SolutionHint& shint);

        private:
            ISQInputData::OptimizationDigitalRegions warmStart(const ISQInputData::OptimizationDigitalRegions& ODR,
                                                               const SolutionHint& shint);

            void reweight(ISQEnergy& energy,const ISQInputData& energyInput);


            ISQInputData updateEnergyInput(const ISQInputData::OptimizationDigitalRegions& ODR,
                                           const ISQInputData& previousEnergyInput);

            ISQInputData::OptimizationDigitalRegions updateODR(const IFlowStepConfig& flowStepConfig,
                                                               const ODRInterface& odrFactory,
                                                               const ISQInputData::OptimizationDigitalRegions& previousODR,
                                                               Solution& solution);

            template<typename TVisitorIterator>
            void solve(Solution& solution,
                       const BCConfigInput& bcInput,
                       const ISQEnergy& energy,
                       const ISQInputData& energyInput,
                       const ISQInputData::OptimizationDigitalRegions& ODR,
                       const ODRInterface& odrFactory,
                       const IFlowStepConfig& flowStepConfig,
                       TVisitorIterator begin,
                       TVisitorIterator end);

            void updateSet(Solution& solution,
                           const ODRInterface& odrFactory,
                           const IFlowStepConfig& flowStepConfig,
                           const ISQInputData& energyInput,
                           const ISQEnergy& energy);

            void printData(const Solution& solution,
                           const ISQEnergy& energy);

        };
    }
}

#include "BCControl.hpp"

#endif //BTools_BOUNDARYCORRECTION_BCCONTROL_H
