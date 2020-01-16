#include "summary-flow/utils.h"

namespace SummaryFlow
{
    namespace Utils
    {
        LinelSet selectLinels(const DigitalSet& ds)
        {
            const Domain& domain = ds.domain();
            LinelSet ls;

            Curve curve;
            DIPaCUS::Misc::computeBoundaryCurve(curve,ds);
            int n = curve.size() - 5;
            auto it = curve.begin();
            while(n-->0)
            {
                ls.insert(*it++);
            }

            return ls;
        }

        PixelSet incidentPixels(const Domain& domain, const LinelSet& ls)
        {
            KSpace kspace;
            kspace.init(domain.lowerBound(),domain.upperBound(),true);

            PixelSet ps;
            for(auto l:ls)
            {
                auto pixels = kspace.sUpperIncident(l);
                for(auto p:pixels) ps.insert( kspace.sCoords(p) );
            }

            return ps;
        }

        DigitalSet eliminatePixels(const DigitalSet& ds, const PixelSet& ps)
        {
            DigitalSet dsOut(ds.domain());
            for(auto p:ds)
            {
                if(ps.find(p)==ps.end())
                {
                    dsOut.insert(p);
                }
            }

            return dsOut;
        }

        DigitalSet eliminatePixels(const DigitalSet& ds, const LinelSet& ls)
        {
            PixelSet ps = SummaryFlow::Utils::incidentPixels(ds.domain(),ls);

            DigitalSet pixelBoundary(ds.domain());
            DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(pixelBoundary,ds);
            DigitalSet diff = SummaryFlow::Utils::eliminatePixels(pixelBoundary,ps);

            return diff;
        }

        DigitalSet imageToDigitalSet(const std::string& imgPath)
        {
            cv::Mat cvImg = cv::imread(imgPath);
            cv::Mat grayscale(cvImg.size(),
                              CV_8UC1);

            if(cvImg.type()!=CV_8UC1)
                cv::cvtColor(cvImg,grayscale,cv::COLOR_RGB2GRAY,1);


            DigitalSet ds( Domain(Point(0,0),Point(grayscale.cols-1,grayscale.rows-1) ) );
            DIPaCUS::Representation::CVMatToDigitalSet(ds,grayscale);
            return ds;
        }

        DigitalSet centerBall(const std::set<Point>& lastSP,double radius, double h)
        {
            DGtal::Z2i::RealPoint avgPt(0,0);
            for(auto p:lastSP) avgPt+=p;
            avgPt/=lastSP.size();
            DigitalSet ball = DIPaCUS::Shapes::ball(h,avgPt[0]*h,avgPt[1]*h,radius);
            DigitalSet ballContour(ball.domain());
            DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::EightNeighborhoodPredicate>(ballContour,ball,1);

            return ballContour;
        }

    }
}