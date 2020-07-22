#ifndef BTOOLS_SHAPE_FLOW_UTILS_H
#define BTOOLS_SHAPE_FLOW_UTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/components/Transform.h>
#include <BTools/core/model/input/ModelParameters.h>

#include "model/ShapeType.h"

namespace ShapeFlow{
namespace Utils{
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;
typedef BTools::Core::ModelParameters ModelParameters;

DigitalSet resolveShape(Shape shape,double gridStep);
void checkBounds(const DigitalSet& ds, const Domain& domain);
cv::Mat createInitialImage(const DigitalSet& _ds,const ModelParameters& modelParameters);

}
}


#endif //BTOOLS_SHAPE_FLOW_UTILS_H
