#ifndef BTOOLS_DATASETCONTROL_H
#define BTOOLS_DATASETCONTROL_H

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <BTools/model/input/BCFlowInput.h>
#include <BTools/model/output/OptOutput.h>

#include <BTools/model/instance/profile/CurvatureProfile.h>
#include <BTools/model/instance/profile/DataTermProfile.h>
#include <BTools/model/instance/Instance.h>
#include <BTools/model/instance/Study.h>

#include <BTools/DataReader.h>
#include <BTools/DataWriter.h>

#include <SCaBOliC/Utils/Utils.h>

#include <BinOCS/BoundaryCorrection/model/CVMatDistribution.h>
#include <BinOCS/BoundaryCorrection/BCApplication.h>
#include <BinOCS/GrabCut/GrabCutApplication.h>

#include "FromSeedControl.h"


namespace BTools
{
    namespace Application
    {
        class DatasetControl
        {
        public:
            typedef BTools::Model::Instance::BCFlowInput BCFlowInput;
            typedef BCFlowInput::BCConfigInput BCInput;
            typedef BTools::Model::Instance::SeedSequenceInput SeedSequenceInput;
            typedef BTools::Model::OptOutput OptOutput;

            typedef BinOCS::BoundaryCorrection::BCApplication BCApplication;
            typedef BinOCS::GrabCut::GrabCutApplication GrabCutApplication;
            typedef BinOCS::RegionSelector::SeedSelectorApplication SeedSelectorApplication;


            typedef SeedSelectorApplication::SelectorOutput SelectorOutput;
            typedef BinOCS::BoundaryCorrection::CVMatDistribution CVMatDistribution;

            typedef BCApplication::BCSolution BCSolution;



        public:
            template<typename TInstanceProfile>
            static void runFlowOnDataset(const std::string& datasetPath,
                                         BCFlowInput bcFlowInputModel,
                                         const std::string& outputFolder);
        };
    }
}

#include "DatasetControl.hpp"

#endif //BTOOLS_DATASETCONTROL
