#ifndef BTOOLS_SUMMARY_FLOW_INPUTREADER_H
#define BTOOLS_SUMMARY_FLOW_INPUTREADER_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <boost/filesystem/operations.hpp>

#include "InputData.h"

namespace SummaryFlow
{
    namespace InputReader
    {
        void usage(int argc,char* argv[]);
        InputData readInput(int argc,char* argv[]);
    }
}

#endif //EXHAUSTIVE_GC_INPUTREADER_H
