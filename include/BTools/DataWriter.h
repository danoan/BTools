#ifndef BTOOLS_DATAWRITER_H
#define BTOOLS_DATAWRITER_H

#include <string>
#include <ostream>

#include "BTools/model/input/BCFlowInput.h"
#include "BTools/model/input/SeedSequenceInput.h"
#include "BTools/model/output/OptOutput.h"
#include "BTools/model/instance/Instance.h"
#include "BTools/model/instance/Study.h"

#include "BTools/utils/strUtils.h"

namespace BTools
{
    namespace DataWriter
    {
        typedef Model::Instance Instance;
        typedef Model::OptOutput OptOutput;
        typedef Model::Study Study;
        typedef Instance::BCFlowInput BCFlowInput;
        typedef Instance::SeedSequenceInput SeedSequenceInput;

        typedef Model::BCFlowInput::BCConfigInput::QPBOSolverType QPBOSolverType;

        void write(const Study&,
                   std::ostream& os);

        void write(const OptOutput& optOutput,
                   std::ostream& os,
                   bool printHeader);

        void write(const SeedSequenceInput& dataToWrite,
                   std::string outputFilepath);

        void writeRect(const SeedSequenceInput& dataToWrite,std::ofstream& ofs);
        void writeMask(const SeedSequenceInput& dataToWrite,std::ofstream& ofs);


        std::string resolveQPBOSolverType(QPBOSolverType solverType);
    };
}

#endif