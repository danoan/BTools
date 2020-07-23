#ifndef BTools_IO_WRITER_H
#define BTools_IO_WRITER_H

#include <string>
#include <ostream>

#include "BTools/core/model/input/ModelParameters.h"
#include "BTools/core/model/input/BCInput.h"

#include "BTools/utils/strUtils.h"

namespace BTools {
namespace IO {
namespace Writer {
typedef BTools::Core::BCInput BCInput;
typedef BTools::Core::ModelParameters ModelParameters;

void write(const BCInput &bcInput,
           std::ostream &os,
           bool printHeader);

}
}
}

#endif //BTools_IO_WRITER_H