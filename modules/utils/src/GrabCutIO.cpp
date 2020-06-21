#include <opencv/highgui.hpp>
#include "BTools/utils/model/GrabCutObject.h"

using namespace BTools::Utils;

namespace BTools{namespace Utils{ namespace GrabCutIO
{
cv::Vec3b FG_SEED_COLOR(0,255,0);
cv::Vec3b BG_SEED_COLOR(120,120,120);
cv::Vec3b PBFG_SEED_COLOR(0,0,255);
}}}

void GrabCutIO::filterColor(const cv::Mat& img,cv::Vec3b& color,cv::Mat& out)
{
    for(int r=0;r<img.rows;++r)
    {
        for(int c=0;c<img.cols;++c)
        {
            if(img.at<cv::Vec3b>(r,c)==color)
            {
                out.at<unsigned char>(r,c)=255;
            }
        }
    }
}

void GrabCutIO::write(const GrabCutObject& gco, const std::string& outputPath)
{
    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());

    cv::FileStorage gcObjectFile(outputPath,cv::FileStorage::WRITE);
    gcObjectFile << "grabCutMask" << gco.grabCutMask;
    gcObjectFile << "segMask" << gco.segMask;
    gcObjectFile << "inputImage" << gco.inputImage;
    gcObjectFile << "seeds" << gco.seeds;

    gcObjectFile.release();
}

GrabCutIO::GrabCutObject GrabCutIO::read(const std::string &grabCutObjectFile)
{
    GrabCutIO::GrabCutObject gco;

    cv::FileStorage grabcutObjectFile(grabCutObjectFile,cv::FileStorage::READ);
    grabcutObjectFile["grabCutMask"] >> gco.grabCutMask;
    grabcutObjectFile["segMask"] >> gco.segMask;
    grabcutObjectFile["inputImage"] >> gco.inputImage;
    grabcutObjectFile["seeds"] >> gco.seeds;

    return gco;
}

void GrabCutIO::getSeedMasks(const GrabCutObject& gco,cv::Mat& fgMask, cv::Mat& bgMask, cv::Mat& pbfgMask)
{
    fgMask = cv::Mat::zeros(gco.seeds.size(),CV_8UC1);
    filterColor(gco.seeds,FG_SEED_COLOR,fgMask);

    bgMask = cv::Mat::zeros(gco.seeds.size(),CV_8UC1);
    filterColor(gco.seeds,BG_SEED_COLOR,bgMask);

    cv::Mat temp = cv::Mat::zeros(gco.seeds.size(),CV_8UC1);
    filterColor(gco.seeds,PBFG_SEED_COLOR,temp);


    pbfgMask = cv::Mat::zeros(gco.seeds.size(),CV_8UC1);
    cv::Rect r = cv::boundingRect(temp);
    cv::rectangle(pbfgMask,r,255,cv::FILLED);
}