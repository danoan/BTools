#ifndef BTools_BCCONFIGINPUT_H
#define BTools_BCCONFIGINPUT_H

#include "SCaBOliC/Optimization/solver/QPBOSolverType.h"

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
            BCConfigInput(unsigned long int radius,
                          double dataTermWeight,
                          double sqTermWeight,
                          double lengthTermWeight,
                          QPBOSolverType solverType):radius(radius),
                                                     dataTermWeight(dataTermWeight),
                                                     sqTermWeight(sqTermWeight),
                                                     lengthTermWeight(lengthTermWeight),
                                                     solverType(solverType){}

            unsigned long int radius;
            double dataTermWeight;
            double sqTermWeight;
            double lengthTermWeight;

            QPBOSolverType solverType;
        };
    }
}

#endif //BTools_BCCONFIGINPUT_H
