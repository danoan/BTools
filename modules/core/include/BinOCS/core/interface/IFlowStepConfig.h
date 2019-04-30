#ifndef BINOCS_IBCPROFILE_H
#define BINOCS_IBCPROFILE_H

#include <DGtal/helpers/StdDefs.h>

#include <SCaBOliC/Core/ODRModel.h>
#include <SCaBOliC/Energy/ISQ/InputData.h>
#include <SCaBOliC/Energy/model/Solution.h>
#include <SCaBOliC/Optimization/solver/QPBOSolverType.h>

namespace BinOCS
{
    namespace Core
    {
        class IFlowStepConfig
        {
        public:
            typedef SCaBOliC::Energy::Solution::LabelsVector LabelsVector;

            typedef SCaBOliC::Core::ODRModel::OptimizationMode OptimizationMode;
            typedef SCaBOliC::Core::ODRModel::ApplicationMode ApplicationMode;

        public:
            virtual OptimizationMode optimizationMode() const=0;
            virtual ApplicationMode applicationMode() const=0;
            virtual bool optInApplicationRegion() const=0;

            virtual void initialSolution(LabelsVector& labelsVector) const=0;
        };
    }
}

#endif //BINOCS_IBCPROFILE_H
