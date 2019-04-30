#ifndef BINOCS_EXPANDOPT_H
#define BINOCS_EXPANDOPT_H

#include <BinOCS/core/interface/IFlowStepConfig.h>

namespace BinOCS
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

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_DilationBoundary; }
            ApplicationMode applicationMode() const{ return ApplicationMode::AM_OptimizationBoundary; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}

#endif //BINOCS_EXPANDOPT_H
