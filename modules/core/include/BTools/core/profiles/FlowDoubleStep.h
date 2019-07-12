#ifndef BTools_FLOWINTERPIXEL_H
#define BTools_FLOWINTERPIXEL_H

#include <BTools/core/interface/IFlowProfile.h>
#include "Correct.h"
#include "CorrectOpt.h"
#include "Expand.h"
#include "ExpandOpt.h"

namespace BTools
{
    namespace Core
    {
        template<typename TStepOne, typename TStepTwo>
        class FlowDoubleStep:public IFlowProfile
        {
        public:
            typedef TStepOne StepOneProfile;
            typedef TStepTwo StepTwoProfile;

        public:
            FlowDoubleStep(StepOneProfile& expand,
                           StepTwoProfile& correct,
                           bool revert=false):_it(0),
                                              _count(0),
                                              _revert(revert),
                                              _firstStep(true),
                                              expand(expand),
                                              correct(correct)
            {}

            FlowDoubleStep(bool revert=false):_it(0),
                                              _count(0),
                                              _revert(revert),
                                              _firstStep(true)
            {}

            bool firstStep() const { return _firstStep; }

            void restart(bool optInRegionApplication)
            {
                _it=0;
                _firstStep=true;_count=0;

                correct=StepTwoProfile(optInRegionApplication);
                expand=StepOneProfile(optInRegionApplication);
            }

            int currentIteration() const{ return _it;}
            const IFlowStepConfig& nextStep()
            {
                ++_count;
                if(_firstStep)
                {
                    if(_count==_inseqFirst)
                    {
                        _firstStep = !_firstStep;
                        _count=0;
                    }

                    if(_revert) return correct; else return expand;
                }
                else
                {
                    if(_count==_inseqSecond)
                    {
                        ++_it;
                        _firstStep = !_firstStep;
                        _count=0;
                    }

                    if(_revert) return expand; else return correct;
                }

            }

        private:
            int _it;
            bool _revert;
            bool _firstStep;

            int _count;
            const int _inseqFirst=1;
            const int _inseqSecond=1;   //TODO::If not 1-1, interpixels doubling must be changed

            StepTwoProfile correct;
            StepOneProfile expand;
        };
    }
}

#endif //BTools_FLOWINTERPIXEL_H

