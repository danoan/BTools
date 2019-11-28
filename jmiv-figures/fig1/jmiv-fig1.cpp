#include <boost/filesystem.hpp>

#include <exhaustive-gc/core/check-elem/CheckableSeedPair.h>
#include <exhaustive-gc/core/control/CurveFromJoints.h>

#include <exhaustive-gc/api/utils/GenerateSeedPairs.h>
#include <exhaustive-gc/api/utils/FilterSeedPairs.h>
#include <exhaustive-gc/api/model/SearchParameters.h>
#include <exhaustive-gc/energy/EnergyInput.h>
#include <exhaustive-gc/energy/EnergyType.h>

#include <magLac/core/base/Range.hpp>
#include <magLac/core/single/Combinator.hpp>


#include <DIPaCUS/base/Shapes.h>
#include <gcurve/utils/displayUtils.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>
#include <DGtal/io/Color.h>
#include "../../ext-projects/cmake-build-release/include/exhaustive-gc/energy/EnergyInput.h"

using namespace DGtal::Z2i;
using namespace ExhaustiveGC::Core;
using namespace ExhaustiveGC::API;
using namespace ExhaustiveGC::Energy;

typedef GenerateSeedPairs::SeedPair SeedPair;
typedef ExhaustiveGC::CheckableSeedPair CheckableSeedPair;
typedef ExhaustiveGC::CurveFromJoints CurveFromJoints;

typedef std::vector< CheckableSeedPair > CheckableSeedPairVector;

void drawGCurve(DGtal::Board2D board, std::vector<CheckableSeedPair>& seedCombination, int jointPairs, const std::string& outputFilePath)
{
    Curve curve;
    CurveFromJoints(curve, seedCombination.data(), jointPairs);

    GCurve::Utils::drawCurve(board,DGtal::Color::Red,DGtal::Color::Red,curve.begin(),curve.end());

    GCurve::Utils::drawCurve(board,DGtal::Color::Green,DGtal::Color::Green,
                             seedCombination[0].data().first.inCirculatorBegin,
                             seedCombination[0].data().first.inCirculatorEnd);

    GCurve::Utils::drawCurve(board,DGtal::Color::Green,DGtal::Color::Green,
                             seedCombination[0].data().first.inCirculatorEnd,
                             seedCombination[0].data().second.outCirculatorBegin+1);

    board << DGtal::CustomStyle(curve.begin()->className() + "/Paving", new DGtal::CustomColors(DGtal::Color::Blue, DGtal::Color::Blue));
    board << seedCombination[0].data().first.linkLinels[0]
          << seedCombination[0].data().second.linkLinels[0];


    board.saveEPS(outputFilePath.c_str());
}

void drawBaseCurves(DGtal::Board2D& board, const GCurve::Range& gcRange)
{
    auto it = gcRange.beginSeed();
    int visited=0;
    while(visited<2)
    {
        if(it->type==GCurve::Seed::MainInner && visited==0)
        {
            visited=1;
            GCurve::Utils::drawCurve(board,DGtal::Color::Silver,DGtal::Color::Silver,it->inCirculatorBegin,it->inCirculatorBegin);
            GCurve::Utils::drawCurve(board,DGtal::Color::Silver,DGtal::Color::Silver,it->outCirculatorBegin,it->outCirculatorBegin);
        }else if(it->type==GCurve::Seed::MainOuter && visited==1)
        {
            visited=2;
            GCurve::Utils::drawCurve(board,DGtal::Color::Silver,DGtal::Color::Silver,it->inCirculatorBegin,it->inCirculatorBegin);
            GCurve::Utils::drawCurve(board,DGtal::Color::Silver,DGtal::Color::Silver,it->outCirculatorBegin,it->outCirculatorBegin);
        }
        ++it;
    }

}

void gluedCurve(const std::string& outputFilePath)
{
    boost::filesystem::path p(outputFilePath);
    boost::filesystem::create_directories(p.remove_filename());


    DigitalSet ds = DIPaCUS::Shapes::square();

    EnergyInput::LinelSet ls;
    EnergyInput energyInput(EnergyType::Elastica,EnergyInput::MDCA,1.0,5,0.001,ls);
    SearchParameters sp(SearchParameters::Strategy::Best, 1, 11, 12,energyInput,2,1000);

    const DGtal::Z2i::Domain& domain = ds.domain();
    KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    GCurve::Range gcRange(ds,5);
    GenerateSeedPairs::SeedPairsList spl;
    GenerateSeedPairs(spl,gcRange);


    FilterSeedPairs(spl,sp.minGCLength,sp.maxGCLength);
    std::cout << spl.size() << " qualified seeds\n";


    CheckableSeedPairVector cspv;
    std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp) mutable {cspv.push_back( CheckableSeedPair(sp) );});


    DGtal::Board2D board;
    board << ds;
    drawBaseCurves(board,gcRange);

    auto range = magLac::Core::addRange(cspv.begin(),cspv.end(),sp.jointPairs);
    auto combinator = magLac::Core::Single::createCombinator(range);
    auto resolver = combinator.resolver();

    typedef decltype(combinator) MyCombinator;
    typedef MyCombinator::MyResolver MyResolver;

    std::vector<CheckableSeedPair> seedCombination(sp.jointPairs);
    int count=0;
    while( combinator.next(resolver) )
    {
        resolver >> seedCombination;

        drawGCurve(board, seedCombination, sp.jointPairs, outputFilePath + "." + std::to_string(count));
        count++;
    }

};

void modelRegions(const std::string& outputFilePath)
{
    using namespace SCaBOliC::Core;

    double radius=3;
    double h=1.0;
    double levels=4;
    double optBand=1;

    DigitalSet square = DIPaCUS::Shapes::square(0.5);
    SCaBOliC::Core::ODRPixels odrPixels(radius,
                                        h,
                                        levels,
                                        ODRModel::LevelDefinition::LD_CloserFromCenter,
                                        ODRModel::FourNeighborhood,
                                        optBand);

    ODRModel ODR = odrPixels.createODR(ODRModel::AM_AroundBoundary,
                                            square);

    DGtal::Board2D board;
    board << DGtal::SetMode(ODR.original.className(),"Paving")
          << square;


    std::string specificStyle = ODR.original.className() + "/Paving";

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Green));
    board << ODR.optRegion;

    board << DGtal::CustomStyle(specificStyle, new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue));
    board << ODR.applicationRegionIn << ODR.applicationRegionOut;

    board.saveEPS(outputFilePath.c_str());

}

int main(int argc, char* argv[])
{
    if(argc <2)
    {
        std::cerr << "Usage: " << argv[0]  << " OutputFolder\n";
        exit(1);
    }

    std::string outputFolder = argv[1];

    gluedCurve(outputFolder + "/glued-curve-example.eps");
    modelRegions(outputFolder + "/square-regions.eps");

    return 0;
}

