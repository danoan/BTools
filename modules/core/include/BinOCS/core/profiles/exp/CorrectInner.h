#ifndef BINOCS_CORRECTINNER_H
#define BINOCS_CORRECTINNER_H

#include <BinOCS/core/interface/IFlowStepConfig.h>

namespace BinOCS
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

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_OriginalBoundary; }
            ApplicationMode applicationMode() const { return ApplicationMode::AM_InternRange; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BINOCS_CORRECTINNER_H
