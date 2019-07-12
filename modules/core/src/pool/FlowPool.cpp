#include "BTools/core/pool/FlowPool.h"

using namespace BTools::Core;

FlowSingleStep<Correct> FlowPool::flowSingleStepConvexities;
FlowSingleStep<Expand> FlowPool::flowSingleStepConcavities;
FlowSingleStep<CorrectOpt> FlowPool::flowSingleStepOpt;

FlowDoubleStep<Expand,Correct> FlowPool::flowDoubleStep;
FlowDoubleStep<ExpandOpt,CorrectOpt> FlowPool::flowDoubleStepOpt;

