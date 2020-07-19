#ifndef BTOOLS_API_H
#define BTOOLS_API_H

#include <functional>

#include <DIPaCUS/components/Morphology.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>

#include "BTools/core/control/modelIteration.h"
#include "BTools/core/model/BCOutput.h"
#include "BTools/core/model/input/BCInput.h"

namespace BTools{
namespace API{
typedef BTools::Core::BCInput BCInput;
typedef BTools::Core::BCOutput BCOutput;

struct CallbackData{
  int iteration;
  std::string windowName;

  const BCInput& bcInput;
  const BCOutput& bcOutput;
};

typedef std::function<void(CallbackData&&)> BCECallback;
void bce(BCOutput& bcOutput, const BCInput& bcInput,BCECallback callback);

}
}

#endif //BTOOLS_API_H

