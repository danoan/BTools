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

    }
}