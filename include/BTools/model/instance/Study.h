#ifndef BTOOLS_MODEL_STUDY_H
#define BTOOLS_MODEL_STUDY_H

#include "Instance.h"

namespace BTools
{
    namespace Model
    {
        struct Study
        {
            std::vector<OptOutput> vectorOfOptOutput;
            std::string studyName;
        };
    }
}

#endif //BTOOLS_MODEL_STUDY_H
