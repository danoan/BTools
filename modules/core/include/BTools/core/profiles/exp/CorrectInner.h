#ifndef BTools_CORRECTINNER_H
#define BTools_CORRECTINNER_H

#include <BTools/core/interface/IFlowStepConfig.h>

namespace BTools
{
    namespace Core
    {
        class CorrectInner:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;

        public:
            CorrectInner(bool optInApplicationRegion=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_CorrectConvexities; }
            ApplicationMode applicationMode() const { return ApplicationMode::AM_InternRange; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }
            bool shrinkingMode() const{ return true; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BTools_CORRECTINNER_H
