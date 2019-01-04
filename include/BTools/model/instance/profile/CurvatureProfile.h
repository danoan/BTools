#ifndef BTOOLS_MODEL_CURVATUREPROFILE_H
#define BTOOLS_MODEL_CURVATUREPROFILE_H

#include "InstanceProfile.h"

namespace BTools
{
    namespace Model
    {
        class CurvatureProfile: public InstanceProfile
        {
        public:
            typedef BinOCS::BoundaryCorrection::BCApplicationInput BCInput;
            typedef InstanceProfile::VariationType VariationType;

        public:
            CurvatureProfile():InstanceProfile(InstanceProfile::Curvature){}

            std::string profileIdentifier(){return "Curvature-";};

            bool fillInstance(Model::BCFlowInput& producedInput)
            {
                if(currI >=2 ) return false;

                std::string inputName = profileIdentifier() + std::to_string( weights[currI]);
                producedInput.inputName = inputName;
                producedInput.bcInput.sqTermWeight = weights[currI];

                currI++;

                return true;
            }

        private:
            int currI = 0;
            double weights[4] = {0,0.25,0.5,1.0};
        };
    }
}
#endif //BTOOLS_MODEL_CURVATUREPROFILE_H
