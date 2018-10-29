#include "AroundBoundaryReasoning.h"

using namespace BTools::Application::Illustration;

template<typename TDigitalBoundedShape>
void AroundBoundaryReasoning::topLeftCorner(Point& tlc, TDigitalBoundedShape& digitalSet)
{
    BOOST_CONCEPT_ASSERT( (DGtal::concepts::CDigitalBoundedShape<TDigitalBoundedShape>) );

    const Domain& domain = digitalSet.getDomain();
    Point curr;
    tlc = Point(domain.upperBound()(0),domain.lowerBound()(1));
    for(auto it=domain.begin();it!=domain.end();++it)
    {
        if(digitalSet(*it))
        {
            curr = *it;
            tlc(0) = curr(0) < tlc(0)?curr(0):tlc(0);
            tlc(1) = curr(1) > tlc(1)?curr(1):tlc(1);
        }
    }
}