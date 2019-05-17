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
            typedef SCaBOliC::Energy::ISQ::InputData::PenalizationMode PenalizationMode;

        public:
            BCConfigInput(){};
            BCConfigInput(double radius,
                          double dataTermWeight,
                          double sqTermWeight,
                          double lengthTermWeight,
                          double penalizationWeight,
                          bool excludeOptPointsFromAreaComputation,
                          bool repeatedImprovement,
                          PenalizationMode penalizationMode,
                          QPBOSolverType solverType):radius(radius),
                                                     dataTermWeight(dataTermWeight),
                                                     sqTermWeight(sqTermWeight),
                                                     lengthTermWeight(lengthTermWeight),
                                                     penalizationWeight(penalizationWeight),
                                                     penalizationMode(penalizationMode),
                                                     excludeOptPointsFromAreaComputation(excludeOptPointsFromAreaComputation),
                                                     repeatedImprovement(repeatedImprovement),
                                                     solverType(solverType){}

            double radius;
            double dataTermWeight;
            double sqTermWeight;
            double lengthTermWeight;
            double penalizationWeight;

            PenalizationMode penalizationMode;
            bool excludeOptPointsFromAreaComputation;
            bool repeatedImprovement;

            QPBOSolverType solverType;
        };
    }
}

#endif //BTools_BCCONFIGINPUT_H
