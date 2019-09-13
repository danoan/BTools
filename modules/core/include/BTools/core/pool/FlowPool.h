#ifndef BTools_FLOWPOOL_H
#define BTools_FLOWPOOL_H

#include <BTools/core/profiles/FlowDoubleStep.h>
#include <BTools/core/profiles/FlowSingleStep.h>

namespace BTools
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
                if(flowProfile==FlowProfile::SingleStepConvexities)
                {
                    flowSingleStepConvexities.restart(optInRegionApplication);
                    return flowSingleStepConvexities;
                }
                else if(flowProfile==FlowProfile::SingleStepConcavities)
                {
                    flowSingleStepConcavities.restart(optInRegionApplication);
                    return flowSingleStepConcavities;
                }
                else if(flowProfile==FlowProfile::SingleStepOpt)
                {
                    flowSingleStepOpt.restart(optInRegionApplication);
                    return flowSingleStepOpt;
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
                else
                {
                    throw std::runtime_error("Flow profile not recognized!");
                }
            }
            static FlowSingleStep<Correct> flowSingleStepConvexities;
            static FlowSingleStep<Expand> flowSingleStepConcavities;
            static FlowSingleStep<CorrectOpt> flowSingleStepOpt;

            static FlowDoubleStep<Expand,Correct> flowDoubleStep;
            static FlowDoubleStep<ExpandOpt,CorrectOpt> flowDoubleStepOpt;


        };
    }
}
#endif //BTools_FLOWPOOL_H
