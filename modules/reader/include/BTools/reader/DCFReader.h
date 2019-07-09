#ifndef BTOOLS_DCFREADER_H
#define BTOOLS_DCFREADER_H

#include <functional>

#include "InputData.h"

namespace BTools
{
    namespace Reader
    {
        namespace DCFReader
        {
            typedef std::function<InputData()> DefaultValues;


            InputData defaultValues();
            void usage(char* argv[],const std::string& extraUsage);
            InputData readInput(int argc,
                                char** argv,
                                const std::string& extraUsage="",
                                DefaultValues df=defaultValues);
        }
    }
}

#endif //BTOOLS_DCFREADER_H
