#ifndef BTools_CORE_IMAGE_DATA_H
#define BTools_CORE_IMAGE_DATA_H

#include <opencv2/core/mat.hpp>
#include <DGtal/helpers/StdDefs.h>

#include <SCaBOliC/Energy/ISQ/Terms/Data/IProbabilityDistribution.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Transform.h>

namespace BTools{
namespace Core{
class ImageData{
 public:
  typedef DGtal::Z2i::Domain Domain;
  typedef DGtal::Z2i::Point Point;
  typedef DGtal::Z2i::DigitalSet DigitalSet;


  typedef SCaBOliC::Energy::ISQ::IProbabilityDistribution<double> MyProbabilityDistribution;
  typedef cv::Mat cvColorImage;

 private:
  DigitalSet colorImageToDigitalSet(const cvColorImage& segResult)
  {
    Domain tempDomain(Point(0,0),
                      Point(segResult.cols-1,
                            segResult.rows-1)
    );
    DigitalSet tempDS(tempDomain);

    //Convert inputImg to 1-channel grayscale image.
    cv::Mat grayscale(segResult.size(),
                      segResult.type());
    if(segResult.type()!=CV_8UC1)
      cv::cvtColor(segResult,grayscale,cv::COLOR_RGB2GRAY,1);
    else
      grayscale = segResult;

    DIPaCUS::Representation::CVMatToDigitalSet(tempDS,
                                               grayscale,
                                               1);

    return tempDS;
  }

 public:
  ImageData(const MyProbabilityDistribution& fgDistr,
            const MyProbabilityDistribution& bgDistr,
            const cvColorImage& inputImage,
            const cvColorImage& grabcutImage,
            const int initialBorder=20)
      :fgDistr(fgDistr),
       bgDistr(bgDistr),
       inputImage(inputImage),
       grabcutImage(grabcutImage)
  {
    DigitalSet tempDS = colorImageToDigitalSet(grabcutImage);
    Point border(initialBorder,initialBorder);

    Point lb,ub;

    tempDS.computeBoundingBox(lb,ub);
    translation = lb-border;

    inputDS = new DigitalSet( DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(tempDS,border) );
    inputDomain = inputDS->domain();

  }

  ~ImageData()
  {
    delete inputDS;
  }

  ImageData(const ImageData& other) = delete;
  ImageData& operator=(const ImageData& other) = delete;

 public:
  const MyProbabilityDistribution& fgDistr;
  const MyProbabilityDistribution& bgDistr;

  const cvColorImage inputImage;
  const cvColorImage grabcutImage;

  const DigitalSet* inputDS;

  Domain inputDomain;
  Point translation;
};
}
}
#endif //BTools_CORE_IMAGE_DATA_H
