#ifndef BTools_FLOWSINGLESTEP_H
#define BTools_FLOWSINGLESTEP_H

#include <BTools/core/interface/IFlowProfile.h>
#include "Correct.h"
#include "CorrectOpt.h"

namespace BTools
{
    namespace Core
    {
        template<typename TStepOne>
        class FlowSingleStep:public IFlowProfile
        {
        public:
            typedef TStepOne StepOneProfile;

        public:
            FlowSingleStep():_it(0)
            {}

            FlowSingleStep(TStepOne correct):_it(0),
                                             correct(correct)
            {}

            void restart(bool optInRegionApplication)
            {
                _it=0;
                correct=StepOneProfile(optInRegionApplication);
            }

            int currentIteration() const{ return _it;}
            const IFlowStepConfig& nextStep()
            {
                ++_it;
                return correct;
            }

        private:
            int _it;

            StepOneProfile correct;
        };
    }
}

#endif //BTools_FLOWSINGLESTEP_H
