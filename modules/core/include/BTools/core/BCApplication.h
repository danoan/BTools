#ifndef BTools_BCAPPLICATION_H
#define BTools_BCAPPLICATION_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <DIPaCUS/base/Representation.h>
#include <SCaBOliC/Core/interface/ODRInterface.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>

#include <BTools/core/control/BCControl.h>

#include <BTools/core/model/input/BCApplicationInput.h>
#include <BTools/core/model/input/ImageDataInput.h>
#include <BTools/core/model/BCAOutput.h>

#include <BTools/utils/imgUtils.h>

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

        private:

            DigitalSet prepareInputDS(const cv::Mat& inputImg);
            void prepareProductImage(BCAOutput& bcaOutput,
                                     const ImageDataInput& imageDataInput);

        };
    }
}

#endif //BTools_BCAPPLICATION_H
