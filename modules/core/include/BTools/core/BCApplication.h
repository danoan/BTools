#ifndef BTools_BCAPPLICATION_H
#define BTools_BCAPPLICATION_H

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#include <DIPaCUS/base/Representation.h>
#include <SCaBOliC/Core/interface/ODRInterface.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>

#include "BTools/core/control/BCControl.h"

#include "BTools/core/model/input/BCInput.h"
#include "BTools/core/model/input/ImageData.h"
#include "BTools/core/model/BCOutput.h"

#include "BTools/utils/imgUtils.h"

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
            typedef BTools::Core::BCInput BCInput;
            typedef BTools::Core::BCOutput BCOutput;

            typedef SCaBOliC::Energy::Solution BCSolution;
            typedef SCaBOliC::Core::ODRInterface ODRInterface;

        public:
            BCApplication(BCOutput& bcOutput,
                          const BCInput& bcInput);

        private:

            DigitalSet prepareInputDS(const cv::Mat& inputImg);
            void prepareProductImage(BCOutput& bcOutput,
                                     const ImageData& imageData);

        };
    }
}

#endif //BTools_BCAPPLICATION_H
