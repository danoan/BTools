#ifndef BINOCS_EXPERIMENTS_EXPROI_H
#define BINOCS_EXPERIMENTS_EXPROI_H

#include <DGtal/io/boards/Board2D.h>

#include <BinOCS/Experiments/model/ExpDataInput.h>
#include "boost/filesystem.hpp"

#include "BinOCS/Application/BoundaryCorrection/model/CVMatDistribution.h"
#include "BinOCS/Application/BoundaryCorrection/BCApplication.h"

#include "BinOCS/Application/GrabCut/GrabCutApplication.h"
#include "BinOCS/Experiments/model/ExpInput.h"
#include "utils.h"

namespace BinOCS
{
    namespace Experiments
    {
        class ExpROI
        {

        public:
            typedef BinOCS::Application::CVMatDistribution CVMatDistribution;
            typedef BinOCS::Application::BCApplication BCApplication;

            typedef BCApplication::BCConfigData BCConfigData;
            typedef BCApplication::BCSolution BCSolution;
            typedef BCApplication::DisplayData DisplayData;

            typedef BinOCS::Application::GrabCutApplication GCApplication;

        public:
            static ExpInput expInput;

        public:

            ExpROI(const std::string& imgFilepath,
                   const cv::Rect& ROI,
                   const std::string& outputFolder);

        private:
            typedef DGtal::Z2i::DigitalSet DigitalSet;

        };
    }
}

#endif //BINOCS_EXPERIMENTS_EXPROI_H
