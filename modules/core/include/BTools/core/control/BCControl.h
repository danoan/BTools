#ifndef BTools_BOUNDARYCORRECTION_BCCONTROL_H
#define BTools_BOUNDARYCORRECTION_BCCONTROL_H

#include <SCaBOliC/Energy/model/Solution.h>
#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include <SCaBOliC/Optimization/solver/QPBOSolverType.h>
#include "SCaBOliC/Core/interface/ODRInterface.h"

#include "BTools/core/model/input/BCApplicationInput.h"

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
                      const BCApplicationInput& bcaInput,
                      const ODRInterface& odrFactory,
                      const DigitalSet& inputDS);

        private:
            void solve(Solution& solution,
                       const BCConfigInput& bcInput,
                       const ISQEnergy& energy,
                       const ISQInputData& energyInput,
                       const ISQInputData::OptimizationDigitalRegions& ODR,
                       const ODRInterface& odrFactory);

            void updateSet(Solution& solution,
                           const ODRInterface& odrFactory,
                           const ISQInputData& energyInput,
                           const ISQEnergy& energy);

            void printData(const Solution& solution,
                           const ISQEnergy& energy);

        };
    }
}

#endif //BTools_BOUNDARYCORRECTION_BCCONTROL_H
