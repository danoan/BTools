#ifndef BINOCS_INPUTDATA_H
#define BINOCS_INPUTDATA_H

#include <iostream>
#include <unistd.h>

namespace GrabCut
{
    struct InputData
    {
        InputData():showSeg(false){}

        std::string imgPath;
        std::string outputObject;
        std::string outputSegImage;

        std::string unknownMask;
        std::string fgSeedMask;
        std::string bgSeedMask;

        bool showSeg;
    };

    void usage(char* argv[]);
    InputData readInput(int argc, char* argv[]);

}

#endif //BINOCS_INPUTDATA_H
