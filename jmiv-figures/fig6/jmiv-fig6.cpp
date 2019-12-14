#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/readers/GenericReader.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>

#include <DIPaCUS/components/SetOperations.h>

#include <DIPaCUS/derivates/Misc.h>

using namespace DGtal::Z2i;

typedef DGtal::DistanceTransformation<DGtal::Z2i::Space, DigitalSet, DGtal::Z2i::L2Metric> DTL2;
typedef DIPaCUS::Representation::Image2D Image2D;

DTL2 interiorDistanceTransform(const Domain& domain, const DigitalSet& original)
{
    return DTL2(domain, original, DGtal::Z2i::l2Metric);
}

DTL2 exteriorDistanceTransform(const Domain& domain, const DigitalSet& original)
{
    DigitalSet d(domain);
    d.assignFromComplement(original);

    return DTL2(domain, d, DGtal::Z2i::l2Metric);
}

DigitalSet level(const DTL2& dtL2, int lessThan, int greaterThan)
{
    DigitalSet d(dtL2.domain());
    for(auto it=dtL2.domain().begin();it!=dtL2.domain().end();++it)
    {
        if(dtL2(*it)<=lessThan && dtL2(*it)>greaterThan) d.insert(*it);
    }

    return d;
}

int main(int argc, char* argv[])
{
    DigitalSet _shape = DIPaCUS::Shapes::square(1.0,0,0,20);
    DigitalSet shape = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_shape);

    std::string flowResultImage = argv[1];
    std::string outputFolder = argv[2];

    boost::filesystem::create_directories(outputFolder);


    Point lb,ub;
    shape.computeBoundingBox(lb,ub);

    DigitalSet ball = DIPaCUS::Shapes::ball(1.0,ub[0],ub[1],10);

    DTL2 innDT = interiorDistanceTransform(shape.domain(),shape);
    DTL2 outDT = exteriorDistanceTransform(shape.domain(),shape);

    DigitalSet optRegion = level(outDT,1,0);
    //optRegion += level(innDT,1,0);

    DigitalSet frgRegion(shape.domain());
    DIPaCUS::SetOperations::setDifference(frgRegion,shape,optRegion);

    DigitalSet frgIntersection(shape.domain());
    DIPaCUS::SetOperations::setIntersection(frgIntersection,frgRegion,ball);

    DigitalSet optIntersection(shape.domain());
    DIPaCUS::SetOperations::setIntersection(optIntersection,optRegion,ball);

    DGtal::Board2D board;
    board << DGtal::SetMode(shape.className(),"Paving");

    board << DGtal::CustomStyle( shape.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
    << shape;

    board.saveEPS( (outputFolder + "/shape.eps").c_str() );

    board
    << DGtal::CustomStyle( frgRegion.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
    << frgRegion
    << DGtal::CustomStyle( optRegion.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Yellow) )
    << optRegion;

    board.saveEPS( (outputFolder + "/shape-opt.eps").c_str() );

    board
    << DGtal::CustomStyle( ball.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Gray) )
    << ball
    << DGtal::CustomStyle( frgIntersection.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Navy) )
    << frgIntersection
    << DGtal::CustomStyle( optIntersection.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color(255,128,0)) )
    << optIntersection;

    board.saveEPS(  (outputFolder + "/shape-opt-ball.eps").c_str());

    {
        Image2D img = DGtal::GenericReader<Image2D>::import(flowResultImage);
        DigitalSet it(img.domain());
        DIPaCUS::Representation::imageAsDigitalSet(it,img);

        Point ub,lb;
        it.computeBoundingBox(lb,ub);
        DigitalSet ball = DIPaCUS::Shapes::ball(1.0,ub[0]-1,ub[1]-1,10);

        board.clear();

        DigitalSet ballIntersection(it.domain());
        DIPaCUS::SetOperations::setIntersection(ballIntersection,it,ball);

        board << DGtal::CustomStyle( frgRegion.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
              << it
              << DGtal::CustomStyle( ball.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Gray) )
              << ball
              << DGtal::CustomStyle( frgIntersection.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Navy) )
              << ballIntersection;

        board.saveEPS( (outputFolder + "/shape-opt-ball-after.eps").c_str() );
    }


    return 0;
}