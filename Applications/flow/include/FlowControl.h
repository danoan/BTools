#ifndef BTOOLS_APPLICATION_FLOWCONTROL_H
#define BTOOLS_APPLICATION_FLOWCONTROL_H

#include <ostream>

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/shapes/parametric/AccFlower2D.h>
#include <DGtal/shapes/parametric/Ball2D.h>
#include <DGtal/shapes/parametric/NGon2D.h>
#include <DGtal/shapes/parametric/Ellipse2D.h>
#include <DGtal/shapes/Shapes.h>
#include <DGtal/io/writers/GenericWriter.h>

#include <SCaBOliC/Utils/Utils.h>

#include <DIPaCUS/base/Representation.h>

#include <BinOCS/BoundaryCorrection/BCApplication.h>
#include <BinOCS/BoundaryCorrection/model/BCApplicationInput.h>

#include "BTools/utils/strUtils.h"
#include "BTools/model/input/BCFlowInput.h"
#include "MockDistribution.h"
#include "PotentialMap.h"


namespace BTools
{
    namespace Application
    {
        namespace Flow
        {
            class FlowControl
            {
            public:
                typedef DGtal::Z2i::DigitalSet DigitalSet;
                typedef DGtal::Z2i::Space Space;
                typedef DGtal::Z2i::Domain Domain;

                typedef DGtal::Shapes<Domain> Shapes;
                typedef DIPaCUS::Representation::Image2D Image2D;

                typedef DGtal::AccFlower2D<Space> Flower;
                typedef DGtal::Ball2D<Space> Ball;
                typedef DGtal::NGon2D<Space> NGon;
                typedef DGtal::Ellipse2D<Space> Ellipse;

                typedef BinOCS::BoundaryCorrection::BCApplication::BCAOutput BCAOutput;
                typedef BinOCS::BoundaryCorrection::BCApplicationInput BCAInput;
                typedef BinOCS::BoundaryCorrection::BCConfigInput BCConfigInput;

                typedef BTools::Model::BCFlowInput BCFlowInput;

            private:
                struct TableEntry
                {
                    TableEntry(Solution& solution, std::string name):solution(solution),
                                                                     name(name){}
                    Solution solution;
                    std::string name;
                };

            public:
                FlowControl(const BCFlowInput& bcFlowInput,
                            const std::string& outputFolder,
                            bool exportRegions);

            private:
                template<class TShape>
                void shapeFlow(TShape s,
                               const BCFlowInput& bcFlowInput,
                               double h,
                               std::string name,
                               std::string imageOutputFolder,
                               bool exportRegions);

                void exportImageFromDigitalSet(const DigitalSet& ds,
                                               const std::string& outputFilepath);

                void exportImageFromDigitalSet(const DigitalSet& ds,
                                               const Domain& domain,
                                               const std::string& outputFilepath);

		        void outputElasticaEnergy(const DigitalSet& ds, std::ostream& os);
                void printTable(const std::vector<TableEntry> &entries,
                                std::ostream &os);
            };
        }
    }
}

#include "FlowControl.hpp"

#endif //BTOOLS_APPLICATION_FLOWCONTROL_H
