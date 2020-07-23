#ifndef BTOOLS_UTILS_DIGUTILS_H
#define BTOOLS_UTILS_DIGUTILS_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/base/Shapes.h>

#include "BTools/core/model/ShapeType.h"

namespace BTools{
namespace Utils{
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef BTools::Core::Shape Shape;
typedef BTools::Core::ShapeType ShapeType;

DigitalSet resolveShape(Shape shape,double gridStep);
}
}

#endif //BTOOLS_UTILS_DIGUTILS_H
