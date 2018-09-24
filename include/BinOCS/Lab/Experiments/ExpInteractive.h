#ifndef BINOCS_EXPERIMENTS_EXPINTERACTIVE_H
#define BINOCS_EXPERIMENTS_EXPINTERACTIVE_H

#include <DGtal/io/boards/Board2D.h>

#include "boost/filesystem.hpp"

#include "BinOCS/Application/BoundaryCorrection/model/CVMatDistribution.h"
#include "BinOCS/Application/BoundaryCorrection/BCApplication.h"

#include "BinOCS/Application/GrabCut/GrabCutApplication.h"

#include <BinOCS/Lab/model/input/ROISequenceInput.h>
#include <BinOCS/Lab/model/input/GrabCorrectionInput.h>
#include <BinOCS/Lab/model/input/GrabCorrectionInput.h>
#include "BinOCS/Lab/model/input/BCorrectionInput.h"
#include "BinOCS/Lab/utils.h"


namespace BinOCS
{
    namespace Lab
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

                ExpInteractive(const Model::GrabCorrectionInput& input,
                               std::string outputFolder);

            private:
                typedef DGtal::Z2i::DigitalSet DigitalSet;

            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_EXPINTERACTIVE_H
