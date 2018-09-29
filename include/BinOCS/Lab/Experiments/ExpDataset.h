#ifndef BINOCS_EXPERIMENTS_EXPDATASET_H
#define BINOCS_EXPERIMENTS_EXPDATASET_H

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "SCaBOliC/Utils/Utils.h"

#include <BinOCS/Lab/model/input/SeedCorrectionInput.h>
#include <BinOCS/Lab/model/instance/GeneralInstance.h>
#include <BinOCS/Lab/model/instance/profile/CurvatureProfile.h>

#include <BinOCS/Application/BoundaryCorrection/model/CVMatDistribution.h>
#include <BinOCS/Application/BoundaryCorrection/BCApplication.h>
#include <BinOCS/Application/GrabCut/GrabCutApplication.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Experiments
        {
            class ExpDataset
            {
            public:
                typedef BinOCS::Application::CVMatDistribution CVMatDistribution;
                typedef BinOCS::Application::BCApplication BCApplication;

                typedef BCApplication::BCConfigData BCConfigData;
                typedef BCApplication::BCSolution BCSolution;
                typedef BCApplication::DisplayData DisplayData;

                typedef BinOCS::Application::GrabCutApplication GCApplication;
                typedef SeedCorrectionInput::SeedInput::SelectorOutput SelectorOutput;

                typedef GeneralInstance<SeedCorrectionInput> MyInstance;

            public:
                ExpDataset(std::string datasetPath,bool ROISelection=true);

                void executeInstance(OptOutput& output,
                                     const BCorrectionInput& bcInput,
                                     const SelectorOutput& selectorOutput,
                                     const std::string& imgFilePath);

            private:
                void executeROICorrection(std::string datasetPathStr);
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_EXPDATASET_H
