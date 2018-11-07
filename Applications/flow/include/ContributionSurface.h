#ifndef BTOOLS_CONTRIBUTIONSURFACE_H
#define BTOOLS_CONTRIBUTIONSURFACE_H

#include "BinOCS/BoundaryCorrection/interface/IBCControlVisitor.h"

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            class ContributionSurface:public BinOCS::BoundaryCorrection::IBCControlVisitor
            {
            public:
                typedef BinOCS::BoundaryCorrection::IBCControlVisitor Base;
                typedef Base::OptimizationData OptimizationData;
                typedef Base::VariableMap VariableMap;

                typedef SCaBOliC::Core::ODRModel ODRModel;

                struct Contribution
                {
                    Contribution(int x,int y,int z, double value):x(x),y(y),z(z),value(value){}

                    int x,y,z;
                    double value;
                };

                typedef DGtal::Z2i::DigitalSet DigitalSet;

                typedef std::vector<Contribution> ContributionVector;
                typedef std::vector<ContributionVector> ContributionMatrix;

                typedef std::unordered_map<int,DGtal::Z2i::Point> ReverseVariableMap;

            public:
                ContributionSurface():Base(){}

                void visit(const OptimizationData& energy,
                           const VariableMap& vm,
                           const ODRModel& odr);

                ReverseVariableMap reverseVariableMap(const VariableMap& vm,
                                                      const ODRModel& odr);

                std::string generateGNUPlotData(const ContributionMatrix& contrM);

            };
        }
    }
}
#endif //BTOOLS_CONTRIBUTIONSURFACE_H
