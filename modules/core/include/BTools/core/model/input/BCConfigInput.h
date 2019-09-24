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
                          int initialDilation,
                          QPBOSolverType solverType,
                          double innerBallCoef,
                          double outerBallCoef):radius(radius),
                                                     dataTermWeight(dataTermWeight),
                                                     sqTermWeight(sqTermWeight),
                                                     lengthTermWeight(lengthTermWeight),
                                                     excludeOptPointsFromAreaComputation(excludeOptPointsFromAreaComputation),
                                                     initialDilation(initialDilation),
                                                     solverType(solverType),
                                                     innerBallCoef(innerBallCoef),
                                                     outerBallCoef(outerBallCoef){}

            double radius;
            double dataTermWeight;
            double sqTermWeight;
            double lengthTermWeight;

            bool excludeOptPointsFromAreaComputation;
            int initialDilation;

            QPBOSolverType solverType;

            double innerBallCoef,outerBallCoef;
        };
    }
}

#endif //BTools_BCCONFIGINPUT_H
