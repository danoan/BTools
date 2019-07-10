#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "GrabCutOutput.h"

namespace GrabCut
{
    class GrabCutApplication
    {
    private:

    public:
        GrabCutApplication(const cv::Mat& cvImg);

        void setFGMask(const std::string& fgMaskPath);
        void setBGMask(const std::string& bgMaskPath);
        void setUnknownMask(const std::string& uknMaskPath);

        GrabCutOutput run();

    private:
        const cv::Mat& cvImg;
        cv::Mat fgMask,bgMask,unknownMask;
    };
}