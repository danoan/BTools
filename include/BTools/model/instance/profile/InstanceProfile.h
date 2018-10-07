#ifndef BINOCS_EXPERIMENTS_INSTANCEPROFILE_H
#define BINOCS_EXPERIMENTS_INSTANCEPROFILE_H

#include "../../input/BCFlowInput.h"

namespace BTools
{
    namespace Model
    {
        class InstanceProfile
        {
        public:
            enum VariationType{Curvature,Length,Data};

        public:
            InstanceProfile(VariationType vt):vt(vt){}

            virtual bool fillInstance(Model::BCFlowInput& producedInput)=0;
            virtual std::string profileIdentifier()=0;

        protected:
            VariationType vt;
        };
    }
}

#endif //BINOCS_EXPERIMENTS_INSTANCEPROFILE_H
