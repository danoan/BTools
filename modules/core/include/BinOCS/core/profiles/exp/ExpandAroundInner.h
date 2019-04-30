#ifndef BTOOLS_EXPANDAROUNDINNER_H
#define BTOOLS_EXPANDAROUNDINNER_H

#include <BinOCS/core/interface/IFlowStepConfig.h>

namespace BinOCS
{
    namespace Core
    {
        class ExpandAroundInner:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;
        public:
            ExpandAroundInner(bool optInApplicationRegion=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_DilationBoundary; }
            ApplicationMode applicationMode() const{ return ApplicationMode::AM_AroundIntern; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BTOOLS_EXPANDAROUNDINNER_H
