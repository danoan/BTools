#include "distance-transform.h"

namespace Fig2
{
    namespace DistanceTransform
    {
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


        void drawDTs(DGtal::Board2D& board, const LevelsDS& levels, const std::string& outputFilepath)
        {
            const DigitalSet& ds = levels.baseDS;
            board << DGtal::SetMode(ds.className(),"Paving");
            board /*<< DGtal::CustomStyle( ds.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::Silver, DGtal::Color::Blue))
          << ds*/
                    << DGtal::CustomStyle( ds.className() + "/Paving",new DGtal::CustomColors(DGtal::Color::None, DGtal::Color::Navy))
                    << levels.innDS << levels.outDS;

            board.saveEPS(outputFilepath.c_str());
        }

        LevelsDS getLevels(double LEVEL, const DigitalSet& base)
        {
            DigitalSet ds = base;

            DTL2 innDT = interiorDistanceTransform(base.domain(),ds);
            DTL2 outDT = exteriorDistanceTransform(base.domain(),ds);

            DigitalSet innLevel = level(innDT,LEVEL,LEVEL-1);
            DigitalSet outLevel = level(outDT,LEVEL,LEVEL-1);

            return LevelsDS(ds,innLevel,outLevel);
        }

        void distanceTransform(double LEVEL, double h, const std::string& outputFolder)
        {
            DigitalSet _ds = DIPaCUS::Shapes::flower(h,0,0,10,5,2);
            DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds);
            const Domain& domain = ds.domain();

            DTL2 innDT = interiorDistanceTransform(domain,ds);
            DTL2 outDT = exteriorDistanceTransform(domain,ds);


            DGtal::Board2D board;
            Wrapper W(ds,outDT,innDT);

            double min=0;
            double max=0;
            for(auto p:domain)if(min>W(p)) min = W(p);
            for(auto p:domain)if(max<W(p)) max = W(p);

            LevelsDS L = getLevels(LEVEL,ds);

            DGtal::Display2DFactory::drawImage<ColorMap>(board, W, min, max);
            drawDTs(board,L,(outputFolder + "/distance-transform.eps").c_str());
            board.clear();

            DGtal::Display2DFactory::drawImage<ColorMap>(board, W, min, max);
            drawDTs(board,L,(outputFolder + "/distance-transform.eps").c_str());
            board.clear();
        }
    }
}
