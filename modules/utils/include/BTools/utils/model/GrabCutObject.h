#ifndef BTools_UTILS_GRABCUTOUTPUT_H
#define BTools_UTILS_GRABCUTOUTPUT_H

#include <opencv2/core.hpp>
#include <boost/filesystem.hpp>
#include <string>

namespace BTools
{
    namespace Utils
    {
        namespace GrabCutIO
        {
            struct GrabCutObject
            {
                cv::Mat grabCutMask;
                cv::Mat segMask;
                cv::Mat inputImage;
                cv::Mat seeds;
            };

            void write(const GrabCutObject& gco, const std::string& outputPath);
            GrabCutObject read(const std::string& grabCutObjectFile);
        }
    }

}

#endif //BTools_UTILS_GRABCUTOUTPUT_H
