#ifndef BTOOLS_API_H
#define BTOOLS_API_H

#include <functional>

#include <DIPaCUS/components/Morphology.h>
#include <SCaBOliC/Core/ODRPixels/ODRPixels.h>
#include <SCaBOliC/Energy/model/Solution.h>

#include "BTools/core/control/modelIteration.h"
#include "BTools/core/model/input/BCInput.h"

namespace BTools{
namespace API{

typedef BTools::Core::BCInput BCInput;
typedef SCaBOliC::Energy::Solution EnergySolution;

enum Event{Start,Iteration,End};

struct CallbackData{
  Event event;

  int iteration;
  std::string windowName;

  const BCInput& bcInput;
  const EnergySolution& solution;
};

typedef std::function<void(CallbackData&&)> BCECallback;
void bce(const BCInput& bcInput,BCECallback callback);

}
}

#endif //BTOOLS_API_H

