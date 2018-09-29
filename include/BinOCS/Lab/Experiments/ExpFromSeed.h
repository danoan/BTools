#ifndef BINOCS_EXPERIMENTS_EXPROI_H
#define BINOCS_EXPERIMENTS_EXPROI_H

#include <DGtal/io/boards/Board2D.h>

#include "boost/filesystem.hpp"

#include "BinOCS/Application/BoundaryCorrection/model/CVMatDistribution.h"
#include "BinOCS/Application/BoundaryCorrection/BCApplication.h"
#include "BinOCS/Application/GrabCut/GrabCutApplication.h"

#include "BinOCS/Lab/model/input/BCorrectionInput.h"
#include "BinOCS/Lab/utils.h"

namespace BinOCS
{
    namespace Lab
        {
        namespace Experiments
        {
            class ExpFromSeed
            {
    
            public:
                typedef BinOCS::Application::CVMatDistribution CVMatDistribution;
                typedef BinOCS::Application::BCApplication BCApplication;

                typedef BCApplication::BCConfigData BCConfigData;
                typedef BCApplication::BCSolution BCSolution;
                typedef BCApplication::DisplayData DisplayData;

                typedef BinOCS::Application::GrabCutApplication GCApplication;
                typedef typename GCApplication::GrabCutResult GrabCutResult;

                typedef BinOCS::Application::SeedSelectorApplication::SelectorOutput SelectorOutput;
    
            public:
    
                ExpFromSeed(const std::string& imgFilePath,
                            const Model::BCorrectionInput& bcInput,
                            const SelectorOutput& selectorOutput,
                            const std::string& outputFolder);
    
            private:
                typedef DGtal::Z2i::DigitalSet DigitalSet;
    
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_EXPROI_H
