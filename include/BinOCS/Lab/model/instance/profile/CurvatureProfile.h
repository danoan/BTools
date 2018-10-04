#ifndef BINOCS_EXPERIMENTS_CURVATUREPROFILE_H
#define BINOCS_EXPERIMENTS_CURVATUREPROFILE_H

#include "InstanceProfile.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            class CurvatureProfile: public InstanceProfile
            {
            public:
                typedef InstanceProfile::VariationType VariationType;

            public:
                CurvatureProfile():InstanceProfile(InstanceProfile::Curvature){}

                std::string profileIdentifier(){return "Curvature-";};

                bool fillInstance(Model::BCorrectionInput& input)
                {
                    if(currI >=4 ) return false;

                    input.sqTermWeight = weights[currI];
                    input.inputName = profileIdentifier() + std::to_string( input.sqTermWeight);

                    currI++;

                    return true;
                }

            private:
                int currI = 0;
                double weights[4] = {0,0.25,0.5,1.0};
            };
        }
    }
}
#endif //BINOCS_EXPERIMENTS_CURVATUREPROFILE_H
