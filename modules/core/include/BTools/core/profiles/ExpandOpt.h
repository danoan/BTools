#ifndef BTools_EXPANDOPT_H
#define BTools_EXPANDOPT_H

#include <BTools/core/interface/IFlowStepConfig.h>

namespace BTools
{
    namespace Core
    {
        class ExpandOpt:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;
        public:
            ExpandOpt(bool optInApplicationRegion=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_CorrectConcavities; }
            ApplicationMode applicationMode() const{ return ApplicationMode::AM_OptimizationBoundary; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }
            bool shrinkingMode() const{ return false; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BTools_EXPANDOPT_H
