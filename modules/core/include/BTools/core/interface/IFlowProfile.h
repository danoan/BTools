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
                    SingleStep,
                    DoubleStepOpt,
                    SingleStepOpt,
                    DoubleStepInner,
                    SingleStepInner,
                    DoubleStepAroundInner,
                    SingleStepAroundInner};
        public:
            virtual int currentIteration() const=0;
            virtual const IFlowStepConfig& nextStep()=0;
            virtual void restart(bool optRegionInApplication)=0;

        };
    }
}

#endif //BTools_IFLOWPROFILE_H