#include "GUIData.h"

namespace SeedSelector
{
GUIData::GUIData(const std::string& windowName,
                 const std::string& outputFolder,
                 cv::Mat cvImg,
                 bool once):windowName(windowName),
                            outputFolder(outputFolder),
                            cvImg(cvImg),
                            once(once),
                            penWidth(4),
                            seedCounter(0),
                            _meProbablyForeground(RectMouseEvent(this->cvImg,cv::Scalar(255,0,0,0))),
                            _meForeground(MaskMouseEvent(this->cvImg,cv::Scalar(0,255,0,0))),
                            _meBackground(MaskMouseEvent(this->cvImg,cv::Scalar(0,0,0,0))),
                            _meCurrent(&this->_meProbablyForeground) {}

GUIData GUIData::initGUIData(const std::string& windowName,
                             const std::string& outputFolder,
                             const std::string& imagePath,
                             bool once)
{
  boost::filesystem::path p(imagePath);
  std::string modifiedOutputFolder = outputFolder + "/" + p.stem().string();
  boost::filesystem::create_directories(modifiedOutputFolder);

  return GUIData( windowName,modifiedOutputFolder,cv::imread(imagePath),once );
}

void GUIData::set(MouseEventType met)
{
  if(met==ProbablyForeground)
  {
    _meCurrent = &_meProbablyForeground;
  }
  else if(met==Foreground)
  {
    _meCurrent = &_meForeground;
  }
  else if(met==Background)
  {
    _meCurrent = &_meBackground;
  }
  else throw std::runtime_error("Mouse event type unknown!");

}

void GUIData::loadContours(const std::string& segImageMask)
{
  using namespace DGtal::Z2i;
  const cv::Vec3b& color=cv::Vec3b(128,255,255);

  cv::Mat segImg = cv::imread(segImageMask,cv::IMREAD_GRAYSCALE);
  Point ub( segImg.cols-1,segImg.rows-1);
  Point lb(0,0);
  Domain domain(lb,ub);
  DigitalSet ds(domain);
  DIPaCUS::Representation::imageAsDigitalSet(ds,segImageMask);

  DigitalSet boundary(domain);
  DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate> (boundary,ds,2);

  Point dims = boundary.domain().upperBound() - boundary.domain().lowerBound() + Point(1,1);
  cv::Mat maskBoundary = cv::Mat::zeros( dims(1),dims(0) ,CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(maskBoundary,boundary);

  cvImg.setTo( color, maskBoundary);
  _meProbablyForeground.restart();
  _meForeground.restart();
  _meBackground.restart();
}

void GUIData::loadPbFgMask(const std::string& pbfgMask)
{
  if(pbfgMask!="")
    _meProbablyForeground.restart(cv::imread(pbfgMask,cv::IMREAD_GRAYSCALE));
}

void GUIData::loadFgMask(const std::string& fgMask)
{
  if(fgMask!="")
    _meForeground.restart(cv::imread(fgMask,cv::IMREAD_GRAYSCALE));
}
void GUIData::loadBgMask(const std::string& bgMask)
{
  if(bgMask!="")
    _meBackground.restart(cv::imread(bgMask,cv::IMREAD_GRAYSCALE));
}

void GUIData::set(IMouseEvent* met)
{
  _meCurrent = met;
}

GUIData::IMouseEvent* GUIData::me()
{
  _meCurrent->penWidth()=penWidth;
  return _meCurrent;
}
}