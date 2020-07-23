#include "utils.h"

namespace ShapeFlow{
namespace Utils{

void checkBounds(const DigitalSet& ds, const Domain& domain)
{
  Point lb,ub;
  ds.computeBoundingBox(lb,ub);

  if(lb(0) <= domain.lowerBound()(0)+1 ||
      lb(1) <= domain.lowerBound()(1)+1 ||
      ub(0) >= domain.upperBound()(0)-1 ||
      ub(1) >= domain.upperBound()(1)-1 )
  {
    throw std::runtime_error("Result image is too big.");
  }

  if(ds.size()<10) throw std::runtime_error("Result image is too small.");
}

cv::Mat createInitialImage(const DigitalSet& _ds,const ModelParameters& modelParameters){
  int borderSize = 20;

  DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(borderSize,borderSize));
  Point dims = ds.domain().upperBound() - ds.domain().lowerBound() + Point(1,1);
  int cols = dims[0];
  int rows = dims[1];

  cv::Mat image = cv::Mat::zeros( rows,cols,CV_8UC1 );
  DIPaCUS::Representation::digitalSetToCVMat(image, ds);

  return image;
}

}
}
