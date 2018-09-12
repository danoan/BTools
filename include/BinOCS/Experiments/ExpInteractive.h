#ifndef BINOCS_EXPERIMENTS_EXPINTERACTIVE_H
#define BINOCS_EXPERIMENTS_EXPINTERACTIVE_H

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
        class ExpInteractive
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

            ExpInteractive(std::string imgFilepath,
                           std::string outputFolder);

        private:
            typedef DGtal::Z2i::DigitalSet DigitalSet;


            void enhance(cv::Mat& imgOutput,
                         const cv::Mat& baseImg,
                         const DigitalSet& enhanceDSMask,
                         double factor);
        };
    }
}

#endif //BINOCS_EXPERIMENTS_EXPINTERACTIVE_H
