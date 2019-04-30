#ifndef BINOCS_UTILS_DATAWRITER_H
#define BINOCS_UTILS_DATAWRITER_H

#include <string>
#include <ostream>

#include "BinOCS/core/model/input/BCFlowInput.h"
#include "BinOCS/utils/model/OptOutput.h"

#include "BinOCS/utils/strUtils.h"

namespace BinOCS
{
    namespace Utils
    {
        namespace DataWriter
        {
            typedef BinOCS::Core::BCFlowInput BCFlowInput;
            typedef BCFlowInput::BCConfigInput::QPBOSolverType QPBOSolverType;

            void write(const OptOutput& optOutput,
                       std::ostream& os,
                       bool printHeader);


            std::string resolveQPBOSolverType(QPBOSolverType solverType);
        };
    }
}

#endif