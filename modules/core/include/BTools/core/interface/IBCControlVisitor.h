#ifndef BTools_BCCONTROLVISITOR_H
#define BTools_BCCONTROLVISITOR_H

#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>

namespace BTools
{
    namespace Core
    {
        class IBCControlVisitor
        {
        public:
            typedef SCaBOliC::Energy::OptimizationData OptimizationData;
            typedef SCaBOliC::Energy::ISQ::VariableMap VariableMap;
            typedef SCaBOliC::Core::ODRModel ODRModel;

        public:
            virtual void visit(const OptimizationData& optData,
                               const VariableMap& vm,
                               const ODRModel& odr)=0;
        };
    }
}
#endif //BTools_BCCONTROLVISITOR_H
