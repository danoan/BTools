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
                virtual std::string profileIdentifier()=0;

            protected:
                VariationType vt;
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_INSTANCEPROFILE_H
