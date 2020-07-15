#ifndef BTOOLS_API_H
#define BTOOLS_API_H

#include <DIPaCUS/components/Morphology.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>

#include "BTools/core/control/modelIteration.h"
#include "BTools/core/model/BCOutput.h"
#include "BTools/core/model/input/BCInput.h"

namespace BTools{
namespace API{
typedef BTools::Core::BCInput BCInput;
typedef BTools::Core::BCOutput BCOutput;

void bce(BCOutput& bcOutput, const BCInput& bcInput);
}
}

#endif //BTOOLS_API_H

