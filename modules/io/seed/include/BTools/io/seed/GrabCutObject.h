#ifndef BTools_IO_SEED_GRABCUTOUTPUT_H
#define BTools_IO_SEED_GRABCUTOUTPUT_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <string>

namespace BTools{
namespace IO{
namespace Seed{
extern cv::Vec3b FG_SEED_COLOR;
extern cv::Vec3b BG_SEED_COLOR;
extern cv::Vec3b PBFG_SEED_COLOR;

struct GrabCutObject
{
  cv::Mat grabCutMask;
  cv::Mat segMask;
  cv::Mat inputImage;
  cv::Mat seeds;
};

void filterColor(const cv::Mat& img,cv::Vec3b& color,cv::Mat& out);
void write(const GrabCutObject& gco, const std::string& outputPath);
void getSeedMasks(const GrabCutObject& gco,cv::Mat& fgMask, cv::Mat& bgMask, cv::Mat& pbfgMask);
GrabCutObject read(const std::string& grabCutObjectFile);

}
}
}

#endif //BTools_IO_SEED_GRABCUTOUTPUT_H
