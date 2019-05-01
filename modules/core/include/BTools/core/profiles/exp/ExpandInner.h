#ifndef BTools_EXPANDINNER_H
#define BTools_EXPANDINNER_H

#include <BTools/core/interface/IFlowStepConfig.h>

namespace BTools
{
    namespace Core
    {
        class ExpandInner:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;
        public:
            ExpandInner(bool optInApplicationRegion=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_DilationBoundary; }
            ApplicationMode applicationMode() const{ return ApplicationMode::AM_InternRange; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BTools_EXPANDINNER_H
