#ifndef BINOCS_EXPERIMENTS_EXPDATASET_H
#define BINOCS_EXPERIMENTS_EXPDATASET_H

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "SCaBOliC/Utils/Utils.h"

#include <BinOCS/Lab/model/input/SeedCorrectionInput.h>
#include <BinOCS/Lab/model/instance/GeneralInstance.h>
#include <BinOCS/Lab/model/instance/profile/CurvatureProfile.h>
#include <BinOCS/Lab/model/instance/profile/DataTermProfile.h>

#include <BinOCS/Application/BoundaryCorrection/model/CVMatDistribution.h>
#include <BinOCS/Application/BoundaryCorrection/BCApplication.h>
#include <BinOCS/Application/GrabCut/GrabCutApplication.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Experiments
        {
            template<typename TInstanceProfile>
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

                typedef TInstanceProfile MyInstanceProfile;

            public:
                ExpDataset(const std::string& datasetPath,
                           BCorrectionInput& bcInput,
                           const std::string& outputFolder);

                void executeInstance(OptOutput& output,
                                     const BCorrectionInput& bcInput,
                                     const SelectorOutput& selectorOutput,
                                     const std::string& imgFilePath);

            private:
                void executeROICorrection(const std::string& datasetPath,
                                          BCorrectionInput& bcInput,
                                          const std::string& outputFolder);
            };
        }
    }
}

#include "ExpDataSet.hpp"

#endif //BINOCS_EXPERIMENTS_EXPDATASET_H
