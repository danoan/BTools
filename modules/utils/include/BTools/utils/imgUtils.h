#ifndef BTools_UTILS_IMGUTILS_H
#define BTools_UTILS_IMGUTILS_H

#include <string>
#include <opencv2/opencv.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/writers/GenericWriter.h>

#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/derivates/Misc.h>

namespace BTools
{
    namespace Utils
    {
        typedef cv::Vec3b ColorType;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Point Point;
        typedef DIPaCUS::Representation::Image2D Image2D;

        void setHighlightedBorder(cv::Mat &img, ColorType color);

        void setHighlightMask(cv::Mat& outputImage, const cv::Mat& baseImage, const cv::Mat& mask);

        void exportImageFromDigitalSet(const DigitalSet& ds,
                                              const std::string& outputFilepath);

        void exportImageFromDigitalSet(const DigitalSet& ds,
                                              const Domain& domain,
                                              const std::string& outputFilepath);
    }
}

#endif //BTools_UTILS_IMGUTILS_H
