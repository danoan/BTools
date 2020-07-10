#ifndef BTools_UTILS_DATAWRITER_H
#define BTools_UTILS_DATAWRITER_H

#include <string>
#include <ostream>

#include "BTools/core/model/input/ModelParameters.h"
#include "BTools/core/model/input/BCInput.h"
#include "BTools/utils/model/OptOutput.h"
#include "BTools/utils/strUtils.h"

namespace BTools
{
    namespace Utils
    {
        namespace DataWriter
        {
            typedef BTools::Core::BCInput BCInput;
            typedef BTools::Core::ModelParameters ModelParameters;

            void write(const OptOutput& optOutput,
                       std::ostream& os,
                       bool printHeader);

        };
    }
}

#endif