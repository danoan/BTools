#ifndef BTools_EXPAND_H
#define BTools_EXPAND_H

#include <BTools/core/interface/IFlowStepConfig.h>

namespace BTools
{
    namespace Core
    {
        class Expand:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;
        public:
            Expand(bool optInApplicationRegion=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_CorrectConcavities; }
            ApplicationMode applicationMode() const{ return ApplicationMode::AM_AroundBoundary; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }
            bool shrinkingMode() const{ return false; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BTools_EXPAND_H
