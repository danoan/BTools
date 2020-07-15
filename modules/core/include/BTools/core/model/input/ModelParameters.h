#ifndef BTools_CORE_MODEL_PARAMETERS_H
#define BTools_CORE_MODEL_PARAMETERS_H

#include <SCaBOliC/Energy/ISQ/InputData.h>
#include <SCaBOliC/Core/model/ODRModel.h>

namespace BTools{
namespace Core{
struct ModelParameters{
  typedef SCaBOliC::Core::ODRModel::LevelDefinition LevelDefinition;

  ModelParameters(){};
  ModelParameters(double radius,
                  double gridStep,
                  double levels,
                  LevelDefinition ld,
                  double dataTermWeight,
                  double sqTermWeight,
                  double lengthTermWeight,
                  int initialDilation)
      :radius(radius),
       gridStep(gridStep),
       levels(levels),
       levelDefinition(ld),
       dataTermWeight(dataTermWeight),
       sqTermWeight(sqTermWeight),
       lengthTermWeight(lengthTermWeight),
       initialDilation(initialDilation){}

  double radius;
  double gridStep;
  double levels;
  LevelDefinition levelDefinition;

  double dataTermWeight;
  double sqTermWeight;
  double lengthTermWeight;

  int initialDilation;
};
}
}

#endif //BTools_CORE_MODEL_PARAMETERS_H
