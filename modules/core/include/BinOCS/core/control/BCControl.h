#ifndef BINOCS_BOUNDARYCORRECTION_BCCONTROL_H
#define BINOCS_BOUNDARYCORRECTION_BCCONTROL_H

#include <SCaBOliC/Energy/model/Solution.h>
#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include <SCaBOliC/Optimization/solver/QPBOSolverType.h>
#include "SCaBOliC/Core/ODRInterface.h"

#include "BinOCS/core/interface/IFlowStepConfig.h"
#include "BinOCS/core/interface/IBCControlVisitor.h"
#include "BinOCS/core/model/input/ImageDataInput.h"
#include "BinOCS/core/model/input/BCConfigInput.h"

namespace BinOCS
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
                      TVisitorIterator end);

        private:
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

#endif //BINOCS_BOUNDARYCORRECTION_BCCONTROL_H
