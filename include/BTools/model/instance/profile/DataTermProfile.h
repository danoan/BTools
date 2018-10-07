#ifndef BINOCS_EXPERIMENTS_DATATERMPROFILE_H
#define BINOCS_EXPERIMENTS_DATATERMPROFILE_H

#include "InstanceProfile.h"

namespace BTools
{
    namespace Model
    {
        class DataTermProfile: public InstanceProfile
        {
        public:
            typedef BinOCS::BoundaryCorrection::BCApplicationInput BCInput;
            typedef InstanceProfile::VariationType VariationType;

        public:
            DataTermProfile():InstanceProfile(InstanceProfile::Data){}

            std::string profileIdentifier(){return "Data-";};

            bool fillInstance(Model::BCFlowInput& producedInput)
            {
                if(currI >=4 ) return false;

                producedInput.bcInput.dataTermWeight = weights[currI];

                std::string inputName = profileIdentifier() + std::to_string( producedInput.bcInput.dataTermWeight);
                producedInput.inputName = inputName;

                currI++;

                return true;
            }


        private:
            int currI = 0;
            double weights[4] = {0,0.5,1.0,2.0};
        };
    }
}

#endif //BINOCS_EXPERIMENTS_DATATERMPROFILE_H
