#ifndef BINOCS_UTILS_STRUTILS_H
#define BINOCS_UTILS_STRUTILS_H

#include <DGtal/helpers/StdDefs.h>

#include <BinOCS/core/model/input/BCFlowInput.h>
#include <BinOCS/utils/model/OptOutput.h>

namespace BinOCS
{
    namespace Utils
    {
        std::string fixedStrLength(int l,std::string str);
        std::string fixedStrLength(int l,double v);
        std::string nDigitsString(int num, int digits);

    }
}

#endif//BINOCS_UTILS_STRUTILS_H
