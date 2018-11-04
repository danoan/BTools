#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "ContributionSurface.h"

using namespace BTools::Application;;

void Illustration::contributionSurface()
{
    typedef SCaBOliC::Core::ODRPixels ODRPixels;

    typedef ODRPixels::OptimizationMode OptimizationMode;
    typedef ODRPixels::ApplicationMode ApplicationMode;
    typedef ODRPixels::CountingMode CountingMode;
    typedef ODRPixels::ApplicationCenter ApplicationCenter;

    typedef SCaBOliC::Core::ODRModel ODRModel;

    typedef DGtal::Z2i::Space Space;
    typedef DGtal::NGon2D<Space> NGon2D;
    typedef DGtal::GaussDigitizer<Space,NGon2D> GaussDigitizer;
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef DGtal::Z2i::Domain Domain;

    typedef SCaBOliC::Energy::ISQEnergy<ODRPixels> Energy;
    typedef Energy::InputData EnergyInput;

    OptimizationMode om = OptimizationMode::OM_OriginalBoundary;
    ApplicationMode am = ApplicationMode::AM_AroundBoundary;
    ApplicationCenter ac = ApplicationCenter::AC_PIXEL;
    CountingMode cm = CountingMode::CM_PIXEL;
    unsigned int radius = 3;

    NGon2D square(0,0,10,4,3.1416/4.0);
    GaussDigitizer gd;
    gd.attach(square);
    gd.init(square.getLowerBound(),square.getUpperBound(),1.0);

    DigitalSet squareDS(gd.getDomain());
    DGtal::Shapes<Domain>::digitalShaper(squareDS,gd);

//    DIPaCUS::Transform::
//
//    cv::Mat mockImage(20,20,CV_8UC1);
//    mockImage = cv::Mat::zeros(mockImage.size(),CV_8UC1);
//
//
//    ODRModel odr = ODRPixels::createODR(om,am,ac,cm,radius,squareDS);
//
//
//    EnergyInput input(odr,)
//    Energy energy(a)
}