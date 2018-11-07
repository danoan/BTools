#ifndef BTOOLS_ELASTICAINPUT_H
#define BTOOLS_ELASTICAINPUT_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/shapes/fromPoints/StraightLineFrom2Points.h>
#include <DGtal/io/boards/Board2D.h>

#include "Inbox.h"
#include "Triangle.h"

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            namespace ElasticaProblem
            {
                typedef DGtal::Z2i::RealPoint RealPoint;
                typedef DGtal::Z2i::Point Point;

                typedef DGtal::Z2i::DigitalSet DigitalSet;
                typedef DGtal::Z2i::Domain Domain;

                typedef DGtal::StraightLineFrom2Points<RealPoint> Line2D;

                class ElasticaInput
                {
                public:
                    ElasticaInput(RealPoint A, RealPoint B, RealPoint tA, RealPoint tB);

                private:
                    static DigitalSet createInputDS(RealPoint A,
                                                    RealPoint B,
                                                    RealPoint tA,
                                                    RealPoint tB);

                    static Intern::Triangle leftTriangle(RealPoint A, RealPoint tA);
                    static Intern::Triangle rightTriangle(RealPoint B, RealPoint tB);

                    static bool isInsideHalfplanes(const std::vector<Line2D> &halfplanes, const Point &p);

                    static bool boundingBox(RealPoint &lb,
                                            RealPoint &ub,
                                            const std::vector<RealPoint> &extremes);

                public:
                    const RealPoint A,B;
                    const RealPoint tA,tB;

                    const DigitalSet inputDS;

                };
            }
        }
    }
}
#endif //BTOOLS_ELASTICAINPUT_H
