#ifndef BTools_FLOWSTEPCONFIG_H
#define BTools_FLOWSTEPCONFIG_H

#include <BTools/core/interface/IFlowStepConfig.h>

namespace BTools
{
    namespace Core
    {
        class Correct:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;

        public:
            Correct(bool optInApplicationRegion=false,
                    bool invertFrgBkg=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_CorrectConvexities; }
            ApplicationMode applicationMode() const { return ApplicationMode::AM_AroundBoundary; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}
#endif //BTools_FLOWSTEPCONFIG_H
