#ifndef BINOCS_EXPERIMENTS_ROICORRECTIONINPUT_H
#define BINOCS_EXPERIMENTS_ROICORRECTIONINPUT_H

#include "BCorrectionInput.h"
#include "ROISequenceInput.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            struct ROICorrectionInput
            {
                ROICorrectionInput(std::string inputName):bcInput(inputName){};

                BCorrectionInput bcInput;
                ROISequenceInput roiInput;
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_ROICORRECTIONINPUT_H
