#ifndef BINOCS_EXPERIMENTS_DATATERMPROFILE_H
#define BINOCS_EXPERIMENTS_DATATERMPROFILE_H

#include "InstanceProfile.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            class DataTermProfile: public InstanceProfile
            {
            public:
                typedef InstanceProfile::VariationType VariationType;

            public:
                DataTermProfile():InstanceProfile(InstanceProfile::Data){}

                std::string profileIdentifier(){return "Data-";};

                bool fillInstance(Model::BCorrectionInput& input)
                {
                    if(currI >=4 ) return false;

                    input.dataTermWeight = weights[currI];
                    input.inputName = profileIdentifier() + std::to_string( input.dataTermWeight);

                    currI++;

                    return true;
                }

            private:
                int currI = 0;
                double weights[4] = {0,0.5,1.0,2.0};
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_DATATERMPROFILE_H
