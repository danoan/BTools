#ifndef BINOCS_EXPERIMENTS_EXPINPUT_H
#define BINOCS_EXPERIMENTS_EXPINPUT_H

#include <SCaBOliC/Optimization/solver/QPBOSolverType.h>
#include <string>

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            struct BCorrectionInput
            {
                typedef SCaBOliC::Optimization::QPBOSolverType QPBOSolverType;

                BCorrectionInput(std::string inputName):inputName(inputName){};

                int maxIterations;
                QPBOSolverType solverType;

                unsigned long int estimatingBallRadius;
                double dataTermWeight;
                double sqTermWeight;
                double lengthTermWeight;

                std::string inputName;
            };
        }
    }
}
#endif //BINOCS_EXPERIMENTS_EXPINPUT_H
