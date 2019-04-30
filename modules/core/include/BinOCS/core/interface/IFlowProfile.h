#ifndef BINOCS_IFLOWPROFILE_H
#define BINOCS_IFLOWPROFILE_H

#include "IFlowStepConfig.h"

namespace BinOCS
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

#endif //BINOCS_IFLOWPROFILE_H