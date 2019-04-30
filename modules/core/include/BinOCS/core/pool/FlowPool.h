#ifndef BINOCS_FLOWPOOL_H
#define BINOCS_FLOWPOOL_H

#include <BinOCS/core/profiles/FlowDoubleStep.h>
#include <BinOCS/core/profiles/FlowSingleStep.h>
#include <BinOCS/core/profiles/exp/CorrectInner.h>
#include <BinOCS/core/profiles/exp/ExpandInner.h>
#include <BinOCS/core/profiles/exp/CorrectAroundInner.h>
#include <BinOCS/core/profiles/exp/ExpandAroundInner.h>

namespace BinOCS
{
    namespace Core
    {
        class FlowPool
        {
        public:
            typedef IFlowProfile::FlowProfile  FlowProfile;
        public:
            static IFlowProfile& getFlow(const FlowProfile& flowProfile,
                                         bool optInRegionApplication)
            {
                if(flowProfile==FlowProfile::SingleStep)
                {
                    flowSingleStep.restart(optInRegionApplication);
                    return flowSingleStep;
                }
                else if(flowProfile==FlowProfile::SingleStepOpt)
                {
                    flowSingleStepOpt.restart(optInRegionApplication);
                    return flowSingleStepOpt;
                }
                else if(flowProfile==FlowProfile::SingleStepInner)
                {
                    flowSingleStepInner.restart(optInRegionApplication);
                    return flowSingleStepInner;
                }
                else if(flowProfile==FlowProfile::DoubleStep)
                {
                    flowDoubleStep.restart(optInRegionApplication);
                    return flowDoubleStep;
                }
                else if(flowProfile==FlowProfile::DoubleStepOpt)
                {
                    flowDoubleStepOpt.restart(optInRegionApplication);
                    return flowDoubleStepOpt;
                }
                else if(flowProfile==FlowProfile::DoubleStepInner)
                {
                    flowDoubleStepInner.restart(optInRegionApplication);
                    return flowDoubleStepInner;
                }else if(flowProfile==FlowProfile::SingleStepAroundInner)
                {
                    flowSingleStepAroundInner.restart(optInRegionApplication);
                    return flowSingleStepAroundInner;
                }else if(flowProfile==FlowProfile::DoubleStepAroundInner)
                {
                    flowDoubleStepAroundInner.restart(optInRegionApplication);
                    return flowDoubleStepAroundInner;
                }
            }
            static FlowSingleStep<Correct> flowSingleStep;
            static FlowSingleStep<CorrectOpt> flowSingleStepOpt;
            static FlowSingleStep<CorrectInner> flowSingleStepInner;
            static FlowSingleStep<CorrectAroundInner> flowSingleStepAroundInner;

            static FlowDoubleStep<Expand,Correct> flowDoubleStep;
            static FlowDoubleStep<ExpandOpt,CorrectOpt> flowDoubleStepOpt;
            static FlowDoubleStep<ExpandInner,CorrectInner> flowDoubleStepInner;
            static FlowDoubleStep<ExpandAroundInner,CorrectAroundInner> flowDoubleStepAroundInner;


        };
    }
}
#endif //BINOCS_FLOWPOOL_H
