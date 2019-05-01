#include "PotentialGraph.h"

using namespace BTools::Application::Flow;

void PotentialGraph::orderedPointFromCurve(OrderedDigitalSet& ods,
                                           const Curve &curve,
                                           bool directIncident)
{
    DIPaCUS::Properties::BoundingBox bb;
    DIPaCUS::Properties::curveBoundingBox(bb,curve.begin(),curve.end());

    Domain domain(bb.lb - Point(1,1),bb.ub + Point(1,1));

    KSpace KCurve;
    KCurve.init(domain.lowerBound(),domain.upperBound(),true);

    DigitalSet ds( domain );
    for(auto it=curve.begin();it!=curve.end();++it)
    {
        if(directIncident)
        {
            Curve::SCell sc = KCurve.sDirectIncident(*it, KCurve.sOrthDir(*it));
            ods.push_back( (sc.preCell().coordinates - Point(1,1) )/2 );
        }
        else
        {
            Curve::SCell sc = KCurve.sIndirectIncident(*it, KCurve.sOrthDir(*it));
            ods.push_back( (sc.preCell().coordinates - Point(1,1) )/2 );
        }
    }

}

void PotentialGraph::orderedDigitalSet(OrderedDigitalSet &out,
                                       const DigitalSet &ds)
{
    typedef DIPaCUS::Representation::Image2D Image2D;


    Image2D image(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(image,ds);

    Curve curve;
    DIPaCUS::Misc::ComputeBoundaryCurve(image,curve,1);

    orderedPointFromCurve(out,curve,true);

}

void PotentialGraph::visit(const OptimizationData &optData,
                           const VariableMap &vm,
                           const ODRModel &odr)
{

}