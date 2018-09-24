#ifndef BINOCS_EXPERIMENTS_EXPDATASET_H
#define BINOCS_EXPERIMENTS_EXPDATASET_H

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "SCaBOliC/Utils/Utils.h"

#include <BinOCS/Lab/Experiments/ExpROISelection.h>

#include <BinOCS/Lab/model/input/ROICorrectionInput.h>
#include <BinOCS/Lab/model/instance/GeneralInstance.h>
#include <BinOCS/Lab/model/instance/profile/CurvatureProfile.h>

#include <BinOCS/Application/GrabCut/GrabCutApplication.h>
#include <BinOCS/Application/BoundaryCorrection/model/CVMatDistribution.h>
#include <BinOCS/Application/BoundaryCorrection/BCApplication.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Experiments
        {
            class ExpDataset
            {
            public:
                typedef Model::ROICorrectionInput ROICInput;
                typedef Model::GeneralInstance<ROICInput> MyInstance;

                typedef BinOCS::Application::CVMatDistribution CVMatDistribution;
                typedef BinOCS::Application::BCApplication BCApplication;

                typedef BCApplication::BCConfigData BCConfigData;
                typedef BCApplication::BCSolution BCSolution;
                typedef BCApplication::DisplayData DisplayData;

                typedef BinOCS::Application::GrabCutApplication GCApplication;

            public:
                ExpDataset(std::string datasetPath,bool ROISelection=true);

                void executeInstance(OptOutput& output,
                                     const BCorrectionInput& bcInput,
                                     const std::string& imgFilePath,
                                     const cv::Rect& ROI);

            private:
                void selectROI(std::string imgFilepath,
                                           std::string outputDir,
                                           std::string filename);

                void datasetROISelection(std::string datasetPathStr);

                void executeROICorrection(std::string datasetPathStr);
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_EXPDATASET_H
