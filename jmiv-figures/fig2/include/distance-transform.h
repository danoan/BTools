#ifndef BTOOLS_JMIV_FIGURES_FIG_2_DISTANCE_TRANSFORM_H
#define BTOOLS_JMIV_FIGURES_FIG_2_DISTANCE_TRANSFORM_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/colormaps/GradientColorMap.h>
#include <DGtal/io/colormaps/HueShadeColorMap.h>
#include <DGtal/base/Common.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>

#include <DIPaCUS/components/SetOperations.h>

#include <DIPaCUS/derivates/Misc.h>
#include <random>

namespace Fig2
{
    namespace DistanceTransform
    {
        using namespace DGtal::Z2i;

        typedef DGtal::DistanceTransformation<DGtal::Z2i::Space, DigitalSet, DGtal::Z2i::L2Metric> DTL2;
        typedef DIPaCUS::Representation::Image2D Image2D;

        typedef DGtal::GradientColorMap<DTL2::Value, 8> ColorMap;

        struct LevelsDS
        {
            LevelsDS(const DigitalSet& baseDS,const DigitalSet& innDS, const DigitalSet& outDS):baseDS(baseDS),innDS(innDS),outDS(outDS){}

            DigitalSet baseDS;
            DigitalSet innDS;
            DigitalSet outDS;
        };

        struct Wrapper
        {
            typedef double Value;
            typedef DGtal::Z2i::Domain Domain;

            Wrapper(const DigitalSet& ds, const DTL2& outDT, const DTL2& innDT):ds(ds),
                                                                                outDT(outDT),
                                                                                innDT(innDT){}

            double operator()(const Point& p) const
            {
                if(ds(p)) return -innDT(p);
                else return outDT(p);
            }

            const Domain& domain() const{ return ds.domain(); }

            const DigitalSet& ds;
            const DTL2& outDT;
            const DTL2& innDT;
        };

        DTL2 interiorDistanceTransform(const Domain& domain, const DigitalSet& original);
        DTL2 exteriorDistanceTransform(const Domain& domain, const DigitalSet& original);

        DigitalSet level(const DTL2& dtL2, int lessThan, int greaterThan);


        void drawDTs(DGtal::Board2D& board, const LevelsDS& levels, const std::string& outputFilepath);

        LevelsDS getLevels(double LEVEL, const DigitalSet& base);

        void distanceTransform(double level, double h, const std::string& outputFolder);
    }
}

#endif //BTOOLS_DISTANCE_TRANSFORM_H
