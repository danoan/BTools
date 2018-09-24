#ifndef BINOCS_EXPERIMENTS_GRABCORRECTIONINPUT_H
#define BINOCS_EXPERIMENTS_GRABCORRECTIONINPUT_H

#include <string>
#include "BCorrectionInput.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            struct GrabCorrectionInput
            {
                GrabCorrectionInput(std::string inputName):bcInput(inputName){};

                std::string imagePath;
                BCorrectionInput bcInput;
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_GRABCORRECTIONINPUT_H
