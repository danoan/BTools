#include "GrabCutApplication.h"

namespace GrabCut
{
GrabCutApplication::GrabCutApplication(const cv::Mat& cvImg):cvImg(cvImg)
{
}

void GrabCutApplication::setFGMask(const std::string& fgMaskPath)
{
  this->fgMask = cv::imread(fgMaskPath,cv::IMREAD_GRAYSCALE);
}

void GrabCutApplication::setPBFGMask(const std::string& lastSegmentationMask)
{
  if(!lastSegmentationMask.empty()){
    this->pbFgMask = cv::imread(lastSegmentationMask,cv::IMREAD_GRAYSCALE);
  }else{
    this->pbFgMask = cv::Mat::zeros(cvImg.size(),CV_8UC1);
  }
}

void GrabCutApplication::setBGMask(const std::string& bgMaskPath)
{
  this->bgMask = cv::imread(bgMaskPath,cv::IMREAD_GRAYSCALE);
}

void GrabCutApplication::setUnknownMask(const std::string& uknMaskPath)
{
  this->unknownMask= cv::imread(uknMaskPath,cv::IMREAD_GRAYSCALE);
}

GrabCutOutput GrabCutApplication::run(const int iterations)
{
  GrabCutOutput gco;
  gco.grabCutMask = cv::Mat::zeros(cvImg.size(),CV_8UC1);

  if(unknownMask.size>0)
  {
    cv::Mat sureBGMask = cv::Mat::zeros(cvImg.size(),CV_8UC1);
    cv::bitwise_not(unknownMask,sureBGMask);

    gco.grabCutMask.setTo(cv::GrabCutClasses::GC_BGD,sureBGMask);
    gco.grabCutMask.setTo(cv::GrabCutClasses::GC_PR_BGD,unknownMask);
  }else
  {
    gco.grabCutMask = cv::GrabCutClasses::GC_PR_BGD;
  }

  gco.grabCutMask.setTo(cv::GrabCutClasses::GC_PR_FGD,this->pbFgMask);
  gco.grabCutMask.setTo(cv::GrabCutClasses::GC_FGD,fgMask);
  gco.grabCutMask.setTo(cv::GrabCutClasses::GC_BGD,bgMask);


  cv::Mat bgModel;
  cv::Mat fgModel;

  cv::grabCut(cvImg,
              gco.grabCutMask,
              cv::Rect(),
              bgModel,
              fgModel,
              iterations,
              cv::GC_INIT_WITH_MASK);


  gco.segMaskResult = cv::Mat::zeros(cvImg.size(),CV_8UC1);

  cv::compare(gco.grabCutMask,
              cv::GC_PR_FGD,
              gco.segMaskResult,
              cv::CMP_EQ);

  gco.segMaskResult.setTo(255,fgMask);

  return gco;
}
}