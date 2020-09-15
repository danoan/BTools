#ifndef BTools_INPUTDATA_H
#define BTools_INPUTDATA_H

#include <iostream>
#include <unistd.h>

namespace GrabCut
{
    struct InputData
    {
        InputData():showSeg(false),iterations(1){}

        std::string imgPath;
        std::string outputObject;
        std::string outputSegImage;

        std::string unknownMask;
        std::string fgSeedMask;
        std::string bgSeedMask;
        std::string lastSegmentationMask;

        int iterations;

        bool showSeg;
    };

    void usage(char* argv[]);
    InputData readInput(int argc, char* argv[]);

}

#endif //BTools_INPUTDATA_H
