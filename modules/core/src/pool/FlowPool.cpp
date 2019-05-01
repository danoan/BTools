#include "BTools/core/pool/FlowPool.h"

using namespace BTools::Core;

FlowSingleStep<Correct> FlowPool::flowSingleStep;
FlowSingleStep<CorrectOpt> FlowPool::flowSingleStepOpt;
FlowSingleStep<CorrectInner> FlowPool::flowSingleStepInner;
FlowSingleStep<CorrectAroundInner> FlowPool::flowSingleStepAroundInner;

FlowDoubleStep<Expand,Correct> FlowPool::flowDoubleStep;
FlowDoubleStep<ExpandOpt,CorrectOpt> FlowPool::flowDoubleStepOpt;
FlowDoubleStep<ExpandInner,CorrectInner> FlowPool::flowDoubleStepInner;
FlowDoubleStep<ExpandAroundInner,CorrectAroundInner> FlowPool::flowDoubleStepAroundInner;

