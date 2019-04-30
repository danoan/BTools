#ifndef BINOCS_UTILS_IMGUTILS_H
#define BINOCS_UTILS_IMGUTILS_H

#include <string>
#include <opencv2/opencv.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DIPaCUS/base/Representation.h>

namespace BinOCS
{
    namespace Utils
    {
        typedef cv::Vec3b ColorType;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Point Point;
        typedef DIPaCUS::Representation::Image2D Image2D;

        void setHighlightedBorder(cv::Mat &img, ColorType color);

        void exportImageFromDigitalSet(const DigitalSet& ds,
                                              const std::string& outputFilepath);

        void exportImageFromDigitalSet(const DigitalSet& ds,
                                              const Domain& domain,
                                              const std::string& outputFilepath);
    }
}

#endif //BINOCS_UTILS_IMGUTILS_H
