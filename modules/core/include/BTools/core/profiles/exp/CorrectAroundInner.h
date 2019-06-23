#ifndef BTOOLS_CORRECTAROUNDINNER_H
#define BTOOLS_CORRECTAROUNDINNER_H

#include <SCaBOliC/Core/model/ODRModel.h>

namespace BTools
{
    namespace Core
    {
        class CorrectAroundInner:public IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Core::ODRModel::OptimizationMode  OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode  ApplicationMode;

        public:
            CorrectAroundInner(bool optInApplicationRegion=false):flagOptInApplicationRegion(optInApplicationRegion){}

            OptimizationMode optimizationMode() const{ return OptimizationMode::OM_CorrectConvexities; }
            ApplicationMode applicationMode() const { return ApplicationMode::AM_AroundIntern; }
            bool optInApplicationRegion() const{ return flagOptInApplicationRegion; }
            bool shrinkingMode() const{ return true; }

            void initialSolution(LabelsVector& labelsVector) const { labelsVector.setZero(); }

        private:
            bool flagOptInApplicationRegion;
        };
    }
}


#endif //BTOOLS_CORRECTAROUNDINNER_H
