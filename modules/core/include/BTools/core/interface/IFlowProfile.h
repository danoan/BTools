#ifndef BTools_IFLOWPROFILE_H
#define BTools_IFLOWPROFILE_H

#include "IFlowStepConfig.h"

namespace BTools
{
    namespace Core
    {
        class IFlowProfile
        {
        public:
            enum FlowProfile{DoubleStep,
                    SingleStepConvexities,
                    SingleStepConcavities,
                    DoubleStepOpt,
                    SingleStepOpt};
        public:
            virtual int currentIteration() const=0;
            virtual bool firstStep() const=0;
            virtual const IFlowStepConfig& nextStep()=0;
            virtual void restart(bool optRegionInApplication)=0;

        };
    }
}

#endif //BTools_IFLOWPROFILE_H