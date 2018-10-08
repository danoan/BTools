#ifndef BTOOLS_STRUTILS_H
#define BTOOLS_STRUTILS_H

#include <DGtal/helpers/StdDefs.h>

#include <BTools/model/input/BCFlowInput.h>
#include <BTools/model/output/OptOutput.h>
#include <BTools/model/input/SeedSequenceInput.h>

namespace BTools
{
    namespace Utils
    {

        std::string fixedStrLength(int l,std::string str);
        std::string fixedStrLength(int l,double v);
        std::string nDigitsString(int num, int digits);

    }
}

#endif//BTOOLS_STRUTILS_H
