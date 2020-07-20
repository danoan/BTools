#ifndef BTools_DATAWRITER_H
#define BTools_DATAWRITER_H

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/estimation/MLPLengthEstimator.h>

#include <DIPaCUS/derivates/Misc.h>
#include <SCaBOliC/Energy/model/Solution.h>
#include <SCaBOliC/Utils/Utils.h>

#include <BTools/core/model/input/BCInput.h>
#include <BTools/core/model/input/ModelParameters.h>
#include <BTools/utils/strUtils.h>


struct ThreadData
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;

    ThreadData(const DigitalSet& ds, double h, double r):ds(ds),h(h),data(true,r),IIValue(-1){}

    const DigitalSet& ds;
    double h;
    SCaBOliC::Utils::ISQEvaluation::IICurvatureExtraData data;
    double IIValue;
};

void threadFn(ThreadData& td);

namespace ShapeFlow
{
    namespace DataWriter
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Curve Curve;

        typedef BTools::Core::ModelParameters ModelParameters;

        typedef BTools::Core::BCInput BCInput;
        typedef SCaBOliC::Energy::Solution EnergySolution;

        struct TableEntry
        {
            TableEntry(const ModelParameters& modelParameters,
                    const EnergySolution& solution,
                    const std::string name):solution(solution),name(name),gridStep(modelParameters.gridStep),radius(modelParameters.radius){}

            EnergySolution solution;
            std::string name;
            double gridStep;
            double radius;
        };

        void outputElasticaMDCA(const DigitalSet& ds,const double h, std::ostream& os);
        void outputElasticaII(const DigitalSet& ds,const double h, const double radius, std::ostream& os);

        double outputShapePerimeter(const DigitalSet& ds,const double h, std::ostream& os);
        double outputShapeArea(const DigitalSet& ds, double gridStep, std::ostream& os);

        void printTable(const std::string& inputName,const std::vector<TableEntry> &entries, std::ostream &os);

        void printFlowMetadata(const ModelParameters& modelParameters,
                                const DigitalSet& dsZero,
                               std::ofstream &ofs);
    }
}



#endif //BTools_DATAWRITER_H
