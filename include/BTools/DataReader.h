#ifndef BTOOLS_DATAHEADER_H
#define BTOOLS_DATAHEADER_H

#include <BTools/model/input/SeedSequenceInput.h>
#include <iostream>

namespace BTools
{
    namespace DataReader
    {
        typedef Model::SeedSequenceInput SeedSequenceInput;


        SeedSequenceInput read(std::string filepath);

        void readRect(SeedSequenceInput& data,std::ifstream& ifs);
        void readMask(SeedSequenceInput& data,std::ifstream& ifs);
    }
}

#endif //BTOOLS_DATAHEADER_H
