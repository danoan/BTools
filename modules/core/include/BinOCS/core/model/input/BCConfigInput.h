#ifndef BINOCS_BCCONFIGINPUT_H
#define BINOCS_BCCONFIGINPUT_H

#include "SCaBOliC/Optimization/solver/QPBOSolverType.h"

namespace BinOCS
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

#endif //BINOCS_BCCONFIGINPUT_H
