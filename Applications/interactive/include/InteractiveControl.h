#ifndef BINOCS_EXPERIMENTS_EXPINTERACTIVE_H
#define BINOCS_EXPERIMENTS_EXPINTERACTIVE_H

#include "boost/filesystem.hpp"

#include <DGtal/io/boards/Board2D.h>
#include "SCaBOliC/Utils/Utils.h"

#include "BinOCS/BoundaryCorrection/model/CVMatDistribution.h"
#include "BinOCS/BoundaryCorrection/BCApplication.h"

#include "BinOCS/GrabCut/GrabCutApplication.h"

#include "BTools/utils/strUtils.h"
#include "BTools/utils/dispUtils.h"
#include "BTools/utils/imgUtils.h"


namespace BTools
{
    namespace Application
    {
        class InteractiveControl
        {

        public:
            typedef BTools::Model::BCFlowInput BCFlowInput;

            typedef BinOCS::BoundaryCorrection::CVMatDistribution CVMatDistribution;
            typedef BinOCS::BoundaryCorrection::BCApplication BCApplication;


            typedef BCApplication::BCAInput BCAInput;
            typedef BCApplication::BCSolution BCSolution;

            typedef BinOCS::GrabCut::GrabCutApplication GCApplication;
            typedef typename GCApplication::GrabCutResult GrabCutResult;

        public:

            InteractiveControl(const BCFlowInput& bcFlowInput,
                               const std::string& imageFilePath,
                               std::string outputFolder);

        private:
            typedef DGtal::Z2i::DigitalSet DigitalSet;

        };
    }
}

#endif //BINOCS_EXPERIMENTS_EXPINTERACTIVE_H
