#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/readers/GenericReader.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/SetOperations.h>
#include <DIPaCUS/derivates/Misc.h>

#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include <SCaBOliC/Energy/ISQ/InputData.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>
#include <SCaBOliC/Core/model/ODRModel.h>

using namespace DGtal::Z2i;

using namespace SCaBOliC::Core;
using namespace SCaBOliC::Energy;
using namespace SCaBOliC::Optimization;

class MockDistribution:public SCaBOliC::Energy::ISQ::IProbabilityDistribution<double>
{
public:

    MockDistribution()
    {
        srand(time(NULL));
    }

    double operator()(Index row, Index col) const
    {
        return 1.0/( ( rand()%20 )+1.1 );
    }

};

std::pair<ODRPixels,ODRModel> createODRPair(const DigitalSet& shape)
{
    double radius=7;
    double gridStep=1.0;
    double levels=0;

    ODRPixels odrPixels(radius,gridStep,levels,ODRModel::LD_CloserFromCenter,ODRPixels::NeighborhoodType::FourNeighborhood);
    ODRModel odr = odrPixels.createODR(ODRPixels::OptimizationMode::OM_CorrectConvexities,
                                       ODRPixels::ApplicationMode::AM_OptimizationBoundary,
                                       shape);

    return std::make_pair(odrPixels,odr);
}

DigitalSet curveEvolution(const DigitalSet& shape)
{
    auto odrPair = createODRPair(shape);
    const ODRPixels& odrPixels = odrPair.first;
    const ODRModel& odr = odrPair.second;


    Point size = shape.domain().upperBound()-shape.domain().lowerBound() + Point(1,1);
    cv::Mat mockImg( size[1],size[0],CV_8UC3);

    MockDistribution mockFgDistr,mockBgDistr;

    ISQEnergy::InputData isqInput(odr,mockImg,mockFgDistr,mockBgDistr,false,false,0,1.0,0);
    ISQEnergy isq(isqInput,odrPixels.handle());

    Solution solution(shape.domain(),isq.numVars());
    isq.solve<QPBOImproveSolver>(solution);

    Solution::LabelsVector notInverted(isq.numVars());
    notInverted.setZero();
    for(int i=0;i<isq.numVars();++i)
    {
        if(solution.labelsVector.coeff(i)==0) notInverted.coeffRef(i) = 1;
    }

    DigitalSet dsOut(shape.domain());
    DigitalSet dsIn = odr.trustFRG;
    odrPixels.handle()->solutionSet(dsOut,
                                    dsIn,
                                    odr,
                                    ODRPixels::OptimizationMode::OM_CorrectConvexities,
                                    notInverted.data(),
                                    isq.vm().pim);

    return dsOut;

}

void beforeOpt(const DigitalSet& shape, const std::string& outputFilepath)
{
    auto odrPair = createODRPair(shape);
    const ODRPixels& odrPixels = odrPair.first;
    const ODRModel& odr = odrPair.second;

    const DigitalSet& frgRegion = odr.trustFRG;
    const DigitalSet& optRegion = odr.optRegion;

    Point lb,ub;
    shape.computeBoundingBox(lb,ub);

    DigitalSet ball = DIPaCUS::Shapes::ball(1.0,ub[0],ub[1],10);

    DigitalSet frgIntersection(shape.domain());
    DIPaCUS::SetOperations::setIntersection(frgIntersection,frgRegion,ball);

    DigitalSet optIntersection(shape.domain());
    DIPaCUS::SetOperations::setIntersection(optIntersection,optRegion,ball);

    DGtal::Board2D board;
    board << DGtal::SetMode(shape.className(),"Paving");

    board << DGtal::CustomStyle( shape.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
          << shape;

    board
            << DGtal::CustomStyle( frgRegion.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
            << frgRegion
            << DGtal::CustomStyle( optRegion.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Yellow) )
            << optRegion
            << DGtal::CustomStyle( ball.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Gray) )
            << ball
            << DGtal::CustomStyle( frgIntersection.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Navy) )
            << frgIntersection
            << DGtal::CustomStyle( optIntersection.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color(255,128,0)) )
            << optIntersection;

    board.saveEPS( outputFilepath.c_str() );
}

void afterOpt(const DigitalSet& shape,const std::string& outputFilepath)
{
    auto odrPair = createODRPair(shape);
    const ODRPixels& odrPixels = odrPair.first;
    const ODRModel& odr = odrPair.second;

    const DigitalSet& frgRegion = odr.trustFRG;
    const DigitalSet& optRegion = odr.optRegion;

    Point lb,ub;
    shape.computeBoundingBox(lb,ub);

    DGtal::Board2D board;
    DigitalSet ball = DIPaCUS::Shapes::ball(1.0,ub[0],ub[1],10);


    DigitalSet frgIntersection(shape.domain());
    DIPaCUS::SetOperations::setIntersection(frgIntersection,frgRegion,ball);

    DigitalSet optIntersection(shape.domain());
    DIPaCUS::SetOperations::setIntersection(optIntersection,optRegion,ball);

    board << DGtal::SetMode(shape.className(),"Paving");

    {
        DigitalSet optDS = curveEvolution(shape);

        Point ub,lb;
        optDS.computeBoundingBox(lb,ub);
        DigitalSet ball = DIPaCUS::Shapes::ball(1.0,ub[0]-1,ub[1]-1,10);

        DigitalSet ballIntersection(optDS.domain());
        DIPaCUS::SetOperations::setIntersection(ballIntersection,optDS,ball);

        board << DGtal::CustomStyle( frgRegion.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
              << optDS
              << DGtal::CustomStyle( ball.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Gray) )
              << ball
              << DGtal::CustomStyle( ballIntersection.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Navy) )
              << ballIntersection;

        board.saveEPS( outputFilepath.c_str() );
    }

}

int main(int argc, char* argv[])
{
    DigitalSet _shape = DIPaCUS::Shapes::square(1.0,0,0,20);
    DigitalSet shape = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_shape);

    std::string outputFolder = argv[1];

    boost::filesystem::create_directories(outputFolder);

    beforeOpt(shape,outputFolder+"/before-opt.eps");
    afterOpt(shape,outputFolder + "/shape-opt-ball-after.eps");



    return 0;
}