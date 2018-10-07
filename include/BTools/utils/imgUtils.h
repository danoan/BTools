#ifndef BTOOLS_IMGUTILS_H
#define BTOOLS_IMGUTILS_H

#include <opencv2/opencv.hpp>

namespace BTools
{
    namespace Utils
    {
        typedef cv::Vec3b ColorType;

        cv::Rect computeBoundingBox(const cv::Mat& img);
        void setHighlightedBorder(cv::Mat &img, ColorType color);
    }
}

#endif //BTOOLS_IMGUTILS_H
