#ifndef BINOCS_EXPERIMENTS_INSTANCEPROFILE_H
#define BINOCS_EXPERIMENTS_INSTANCEPROFILE_H

#include <BinOCS/Lab/model/input/BCorrectionInput.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            class InstanceProfile
            {
            public:
                enum VariationType{Curvature,Length,Data};

            public:
                InstanceProfile(VariationType vt):vt(vt){}

                virtual bool fillInstance(BCorrectionInput& input)=0;

            protected:
                void standardInput(BCorrectionInput& input)
                {
                    input.maxIterations = 5;
                    input.lengthTermWeight = 1.0;
                    input.dataTermWeight = 1.0;
                    input.sqTermWeight = 1.0;
                    input.estimatingBallRadius = 3;
                    input.solverType = Model::BCorrectionInput::QPBOSolverType::ImproveProbe;
                }

            protected:
                VariationType vt;
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_INSTANCEPROFILE_H
