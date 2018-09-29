#ifndef BINOCS_EXPERIMENTS_SEEDCORRECTIONINPUT_H
#define BINOCS_EXPERIMENTS_SEEDCORRECTIONINPUT_H

#include "BCorrectionInput.h"
#include "SeedSequenceInput.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            struct SeedCorrectionInput
            {
                typedef BCorrectionInput BCInput;
                typedef SeedSequenceInput SeedInput;

                SeedCorrectionInput(std::string inputName):bcInput(inputName){};

                BCInput bcInput;
                SeedInput seedInput;
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_SEEDCORRECTIONINPUT_H
