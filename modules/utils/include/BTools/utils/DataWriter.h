#ifndef BTools_UTILS_DATAWRITER_H
#define BTools_UTILS_DATAWRITER_H

#include <string>
#include <ostream>

#include "BTools/core/model/input/BCFlowInput.h"
#include "BTools/utils/model/OptOutput.h"

#include "BTools/utils/strUtils.h"

namespace BTools
{
    namespace Utils
    {
        namespace DataWriter
        {
            typedef BTools::Core::BCFlowInput BCFlowInput;
            typedef BCFlowInput::BCConfigInput::QPBOSolverType QPBOSolverType;

            void write(const OptOutput& optOutput,
                       std::ostream& os,
                       bool printHeader);


            std::string resolveQPBOSolverType(QPBOSolverType solverType);
        };
    }
}

#endif