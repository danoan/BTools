#include "FlowControl.h"

using namespace BTools::Application::Flow;

template<class TShape>
FlowControl::DigitalSet FlowControl::digitizeShape(const TShape shape,
                                      double h)
{
    typedef DGtal::GaussDigitizer<Space,TShape> MyGaussDigitizer;
    MyGaussDigitizer gd;

    gd.attach(shape);
    gd.init(shape.getLowerBound() + DGtal::Z2i::RealPoint(0,0),
            shape.getUpperBound() + DGtal::Z2i::RealPoint(0,0),h);

    DigitalSet _ds(gd.getDomain());
    Shapes::digitalShaper(_ds,gd);

    return _ds;
}
