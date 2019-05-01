#ifndef BTools_BCAPPLICATION_H
#define BTools_BCAPPLICATION_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <DIPaCUS/base/Representation.h>
#include <SCaBOliC/Core/ODRInterface.h>

#include <BTools/core/control/BCControl.h>

#include <BTools/core/profiles/Expand.h>
#include <BTools/core/profiles/Correct.h>
#include <BTools/core/profiles/FlowSingleStep.h>
#include <BTools/core/profiles/FlowDoubleStep.h>

#include <BTools/core/model/input/BCApplicationInput.h>
#include <BTools/core/model/input/ImageDataInput.h>
#include <BTools/core/model/BCAOutput.h>

#include <BTools/core/interface/IFlowProfile.h>

#include <BTools/core/pool/FlowPool.h>
#include <BTools/core/pool/ODRPool.h>


namespace BTools
{
    namespace Core
    {
        class BCApplication
        {
        private:
            typedef DIPaCUS::Representation::DigitalSet DigitalSet;
            typedef DIPaCUS::Representation::Image2D Image2D;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

        public:
            typedef BTools::Core::BCApplicationInput BCAInput;
            typedef BTools::Core::BCApplicationOutput BCAOutput;

            typedef SCaBOliC::Energy::Solution BCSolution;
            typedef SCaBOliC::Core::ODRInterface ODRInterface;

        public:
            BCApplication(BCAOutput& bcaOutput,
                          const BCAInput& bcaInput,
                          int maxIterations,
                          bool displayEachIteration);

            template<typename TVisitorIterator>
            BCApplication(BCAOutput& bcaOutput,
                          const BCAInput& bcaInput,
                          int maxIterations,
                          bool displayEachIteration,
                          TVisitorIterator begin,
                          TVisitorIterator end);

        private:

            DigitalSet prepareInputDS(const cv::Mat& inputImg);
            void prepareProductImage(BCAOutput& bcaOutput,
                                     const ImageDataInput& imageDataInput);

        };
    }
}

#include "BCApplication.hpp"

#endif //BTools_BCAPPLICATION_H
