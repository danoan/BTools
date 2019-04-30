#ifndef BINOCS_DATAWRITER_H
#define BINOCS_DATAWRITER_H

#include <vector>
#include <iostream>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/estimation/MLPLengthEstimator.h>

#include <DIPaCUS/derivates/Misc.h>
#include <SCaBOliC/Utils/Utils.h>

#include <BinOCS/core/model/BCAOutput.h>
#include <BinOCS/core/model/input/BCFlowInput.h>
#include <BinOCS/utils/strUtils.h>

namespace ShapeFlow
{
    namespace DataWriter
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Curve Curve;
        typedef BinOCS::Core::BCFlowInput BCFlowInput;
        typedef BinOCS::Core::BCApplicationOutput::EnergySolution EnergySolution;

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

        void printFlowMetadata(const BCFlowInput &bcFlowInput,
                               std::ofstream &ofs);
    }
}



#endif //BINOCS_DATAWRITER_H
