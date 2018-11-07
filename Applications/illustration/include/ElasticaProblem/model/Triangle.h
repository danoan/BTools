#ifndef BTOOLS_TRIANGLE_H
#define BTOOLS_TRIANGLE_H

#include <DGtal/shapes/fromPoints/StraightLineFrom2Points.h>
#include <DGtal/helpers/StdDefs.h>

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            namespace ElasticaProblem
            {
                namespace Intern
                {
                    typedef DGtal::Z2i::RealPoint RealPoint;
                    typedef DGtal::StraightLineFrom2Points<RealPoint> Line2D;

                    struct Triangle
                    {
                        Triangle(Line2D side,
                                 Line2D bottom,
                                 Line2D hypotenuse) : side(side), bottom(bottom), hypotenuse(hypotenuse) 
                        {};

                        const Line2D side;
                        const Line2D bottom;
                        const Line2D hypotenuse;
                    };
                }
            }
        }
    }
}

#endif //BTOOLS_TRIANGLE_H
