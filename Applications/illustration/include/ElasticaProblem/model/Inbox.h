#ifndef BTOOLS_INBOX_H
#define BTOOLS_INBOX_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/shapes/fromPoints/StraightLineFrom2Points.h>

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

                    struct Inbox
                    {
                        Inbox(RealPoint A,
                              RealPoint B,
                              RealPoint tA,
                              RealPoint tB);

                        Line2D left;
                        Line2D bottom;
                        Line2D right;
                        Line2D top;
                    };

                }
            }
        }
    }
}

#endif //BTOOLS_INBOX_H
