#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>
#include "DGtal/geometry/curves/estimation/MLPLengthEstimator.h"

#include "DIPaCUS/base/Shapes.h"
#include "DIPaCUS/base/Representation.h"
#include "DIPaCUS/derivates/Misc.h"

using namespace DGtal;
using namespace DGtal::Z2i;

int main()
{
    typedef DIPaCUS::Representation::Image2D Image2D;

    DigitalSet squareDS = DIPaCUS::Shapes::square();
    Image2D squareImg(squareDS.domain());
    DIPaCUS::Representation::digitalSetToImage(squareImg,squareDS);

    Curve curve;
    DIPaCUS::Misc::ComputeBoundaryCurve(squareImg,curve,1);

    KSpace kspace;
    kspace.init(squareDS.domain().lowerBound(),squareDS.domain().upperBound(),true);


    typedef ConstRangeAdapter<Curve::ConstIterator,functors::SCellToPoint<KSpace>,Point> MyConstRangeAdapter;
    MyConstRangeAdapter curvePointAdapter(curve.begin(),
                                          curve.end(),
                                          functors::SCellToPoint<KSpace>(kspace));


    MLPLengthEstimator<MyConstRangeAdapter::ConstIterator> mlpLengthEstimator;
    mlpLengthEstimator.init(1,curvePointAdapter.begin(),curvePointAdapter.end(),true);

    std::cout << mlpLengthEstimator.eval() << "\n";

    Board2D board;
    board << squareDS;
    board.saveEPS("square.eps");

    return 0;
}