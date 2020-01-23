#include "glued-curve.h"

namespace Fig2
{
    namespace GluedCurve
    {
        void gluedCurve(const std::string& outputFilePath)
        {
            typedef GenerateSeedPairs::SeedPair SeedPair;
            typedef ExhaustiveGC::CheckableSeedPair CheckableSeedPair;
            typedef ExhaustiveGC::CurveFromJoints CurveFromJoints;

            typedef std::vector< CheckableSeedPair > CheckableSeedPairVector;


            DigitalSet ds = DIPaCUS::Shapes::square();

            EnergyInput::LinelSet fixedLinels;
            EnergyInput energyInput(EnergyType::Elastica,EnergyInput::MDCA,1.0,5,0.001,fixedLinels);
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

            auto mainC = gcRange.beginSeed()->inCirculatorBegin;
            auto outC = gcRange.beginSeed()->outCirculatorBegin;

            GCurve::Utils::drawCurve(board,DGtal::Color::Silver,DGtal::Color::Silver,mainC,mainC);
            GCurve::Utils::drawCurve(board,DGtal::Color::Silver,DGtal::Color::Silver,outC,outC);

            auto range = magLac::Core::addRange(cspv.begin(),cspv.end(),sp.jointPairs);
            auto combinator = magLac::Core::Single::createCombinator(range);
            auto resolver = combinator.resolver();

            typedef decltype(combinator) MyCombinator;
            typedef MyCombinator::MyResolver MyResolver;

            std::vector<CheckableSeedPair> seedCombination(sp.jointPairs);
            while( combinator.next(resolver) )
            {
                resolver >> seedCombination;
                if(seedCombination[0].data().first.type==GCurve::Seed::SeedType::MainOuter) break;
            }


            Curve curve;
            CurveFromJoints(curve, seedCombination.data(), sp.jointPairs);

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

        };
    }
}