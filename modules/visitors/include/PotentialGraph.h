#ifndef BTOOLS_POTENTIALGRAPH_H
#define BTOOLS_POTENTIALGRAPH_H

#include <BinOCS/BoundaryCorrection/interface/IBCControlVisitor.h>

namespace BTools
{
    namespace Application
    {
        namespace Flow
        {
            typedef BinOCS::BoundaryCorrection::IBCControlVisitor IBCControlVisitor;

            class PotentialGraph:public IBCControlVisitor
            {
            public:
                typedef DGtal::Z2i::Point Point;
                typedef DGtal::Z2i::DigitalSet DigitalSet;
                typedef DGtal::Z2i::KSpace KSpace;
                typedef DGtal::Z2i::Domain Domain;
                typedef DGtal::Z2i::Curve Curve;

                typedef std::vector<Point> OrderedDigitalSet;

            public:
                void visit(const OptimizationData& optData,
                           const VariableMap& vm,
                           const ODRModel& odr);

            private:
                void orderedPointFromCurve(OrderedDigitalSet& ods,
                                           const Curve &curve,
                                           bool directIncident);

                void orderedDigitalSet(OrderedDigitalSet &out,
                                       const DigitalSet &ds);
            };
        }
    }
}

#endif //BTOOLS_POTENTIALGRAPH_H
