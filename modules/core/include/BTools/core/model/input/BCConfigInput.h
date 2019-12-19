#ifndef BTools_BCCONFIGINPUT_H
#define BTools_BCCONFIGINPUT_H

#include "SCaBOliC/Optimization/solver/QPBOSolverType.h"
#include "SCaBOliC/Energy/ISQ/InputData.h"

namespace BTools
{
    namespace Core
    {
        struct BCConfigInput
        {
        public:
            typedef SCaBOliC::Optimization::QPBOSolverType QPBOSolverType;

        public:
            BCConfigInput(){};
            BCConfigInput(double radius,
                          double dataTermWeight,
                          double sqTermWeight,
                          double lengthTermWeight,
                          bool excludeOptPointsFromAreaComputation,
                          bool uniformPerimeter,
                          int initialDilation,
                          QPBOSolverType solverType,
                          double innerBallCoeff,
                          double outerBallCoeff):radius(radius),
                                                     dataTermWeight(dataTermWeight),
                                                     sqTermWeight(sqTermWeight),
                                                     lengthTermWeight(lengthTermWeight),
                                                     excludeOptPointsFromAreaComputation(excludeOptPointsFromAreaComputation),
                                                     uniformPerimeter(uniformPerimeter),
                                                     initialDilation(initialDilation),
                                                     solverType(solverType),
                                                     innerBallCoeff(innerBallCoeff),
                                                     outerBallCoeff(outerBallCoeff){}

            double radius;
            double dataTermWeight;
            double sqTermWeight;
            double lengthTermWeight;

            bool excludeOptPointsFromAreaComputation;
            bool uniformPerimeter;
            int initialDilation;

            QPBOSolverType solverType;

            double innerBallCoeff,outerBallCoeff;
        };
    }
}

#endif //BTools_BCCONFIGINPUT_H
