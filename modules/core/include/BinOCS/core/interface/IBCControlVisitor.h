#ifndef BINOCS_BCCONTROLVISITOR_H
#define BINOCS_BCCONTROLVISITOR_H

#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>

namespace BinOCS
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
#endif //BINOCS_BCCONTROLVISITOR_H
