#ifndef BTools_DATAWRITER_H
#define BTools_DATAWRITER_H

#include <vector>
#include <iostream>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/estimation/MLPLengthEstimator.h>

#include <DIPaCUS/derivates/Misc.h>
#include <SCaBOliC/Utils/Utils.h>

#include <BTools/core/model/BCAOutput.h>
#include <BTools/core/model/input/BCApplicationInput.h>
#include <BTools/core/model/input/BCConfigInput.h>
#include <BTools/utils/strUtils.h>

namespace ShapeFlow
{
    namespace DataWriter
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Curve Curve;
        typedef BTools::Core::BCApplicationInput BCApplicationInput;
        typedef BTools::Core::BCConfigInput BCConfigInput;
        typedef BTools::Core::BCApplicationOutput::EnergySolution EnergySolution;

        struct TableEntry
        {
            TableEntry(EnergySolution& solution, std::string name):solution(solution),
                                                                   name(name){}
            EnergySolution solution;
            std::string name;
        };

        void outputElasticaEnergy(const DigitalSet& ds, std::ostream& os);
        void outputShapePerimeter(const DigitalSet& ds, std::ostream& os);

        void printTable(const std::string& inputName,const std::vector<TableEntry> &entries, std::ostream &os);

        void printFlowMetadata(const BCApplicationInput &bcaInput,
        const DigitalSet& dsZero,
                               std::ofstream &ofs);
    }
}



#endif //BTools_DATAWRITER_H
