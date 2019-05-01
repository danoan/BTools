#ifndef BTools_UTILS_STRUTILS_H
#define BTools_UTILS_STRUTILS_H

#include <DGtal/helpers/StdDefs.h>

#include <BTools/core/model/input/BCFlowInput.h>
#include <BTools/utils/model/OptOutput.h>

namespace BTools
{
    namespace Utils
    {
        std::string fixedStrLength(int l,std::string str);
        std::string fixedStrLength(int l,double v);
        std::string nDigitsString(int num, int digits);

    }
}

#endif//BTools_UTILS_STRUTILS_H
