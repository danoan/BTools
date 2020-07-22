#include "utils.h"

namespace ShapeFlow{
namespace Utils{

DigitalSet resolveShape(Shape shape,double gridStep)
{
  int radius=20;
  if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
  else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
  else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
  else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
  else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
  else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
  else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
  else if(shape.type==ShapeType::Wave) return DIPaCUS::Shapes::wave(gridStep,1200,radius*3,radius*6,0.01);
  else if(shape.type==ShapeType::Bean) return DIPaCUS::Shapes::bean(gridStep,0,0,0.1);
  else
  {
    cv::Mat img = cv::imread(shape.imagePath,CV_8UC1);
    Domain domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(img.cols-1,img.rows-1) );
    DigitalSet ds(domain);
    DIPaCUS::Representation::CVMatToDigitalSet(ds,img,1);
    return ds;
  }
}

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
