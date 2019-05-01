#ifndef BTools_INPUTDATA_H
#define BTools_INPUTDATA_H

#include <iostream>
#include <string>
#include <unistd.h>

namespace SeedSelector
{
    struct InputData
    {
        InputData():once(false){}

        std::string outputFolder;
        std::string imagePath;

        std::string unknownImageMask;
        std::string fgImageMask;
        std::string bgImageMask;

        bool once;
    };

    void usage(char* argv[]);
    InputData readInput(int argc, char* argv[]);
}

#endif //BTools_INPUTDATA_H
