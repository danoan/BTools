#ifndef BINOCS_BCAPPLICATION_H
#define BINOCS_BCAPPLICATION_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <DIPaCUS/base/Representation.h>
#include <SCaBOliC/Core/ODRInterface.h>

#include <BinOCS/core/control/BCControl.h>

#include <BinOCS/core/profiles/Expand.h>
#include <BinOCS/core/profiles/Correct.h>
#include <BinOCS/core/profiles/FlowSingleStep.h>
#include <BinOCS/core/profiles/FlowDoubleStep.h>

#include <BinOCS/core/model/input/BCApplicationInput.h>
#include <BinOCS/core/model/input/ImageDataInput.h>
#include <BinOCS/core/model/BCAOutput.h>

#include <BinOCS/core/interface/IFlowProfile.h>

#include <BinOCS/core/pool/FlowPool.h>
#include <BinOCS/core/pool/ODRPool.h>


namespace BinOCS
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
            typedef BinOCS::Core::BCApplicationInput BCAInput;
            typedef BinOCS::Core::BCApplicationOutput BCAOutput;

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

#endif //BINOCS_BCAPPLICATION_H
