#ifndef BTOOLS_APPLICATION_DATASET_FROMSEEDCONTROL_H
#define BTOOLS_APPLICATION_DATASET_FROMSEEDCONTROL_H

#include <DGtal/io/boards/Board2D.h>

#include "boost/filesystem.hpp"

#include <SCaBOliC/Utils/Utils.h>

#include "BinOCS/BoundaryCorrection/model/CVMatDistribution.h"
#include "BinOCS/BoundaryCorrection/BCApplication.h"
#include "BinOCS/BoundaryCorrection/model/input/BCConfigInput.h"
#include "BinOCS//GrabCut/GrabCutApplication.h"
#include <BinOCS/API.h>

#include "BTools/utils/strUtils.h"
#include "BTools/utils/imgUtils.h"

namespace BTools
{
    namespace Application
    {
        class FromSeedControl
        {
        public:
            typedef BTools::Model::BCFlowInput BCFlowInput;
            
            typedef BinOCS::BoundaryCorrection::CVMatDistribution CVMatDistribution;
            typedef BinOCS::BoundaryCorrection::BCApplication BCApplication;

            typedef BTools::Model::OptOutput OptOutput;

            typedef BCApplication::BCAInput BCAInput;
            typedef BCApplication::BCSolution BCSolution;

            typedef BinOCS::GrabCut::GrabCutApplication GCApplication;
            typedef typename GCApplication::GrabCutResult GrabCutResult;

            typedef BinOCS::RegionSelector::SeedSelectorApplication::SelectorOutput SelectorOutput;

        private:
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
        public:

            FromSeedControl(OptOutput& output,
                            const std::string& imgFilePath,
                            const BCFlowInput& bcFlowInput,
                            const SelectorOutput& selectorOutput,
                            const std::string& outputFolder);

        };
    }
}

#endif //BTOOLS_APPLICATION_DATASET_FROMSEEDCONTROL_H
