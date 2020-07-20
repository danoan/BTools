#ifndef BTOOLS_APPLICATION_SHAPE_FLOW_INPUTREADER_H
#define BTOOLS_APPLICATION_SHAPE_FLOW_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BTools/core/model/input/ModelParameters.h"
#include "ShapeType.h"


namespace ShapeFlow{
struct InputData
{
  typedef BTools::Core::ModelParameters ModelParameters;
  typedef ModelParameters::LevelDefinition LevelDefinition;

  InputData();

  Shape shape;
  double gridStep;

  int radius;
  int iterations;
  double levels;

  ModelParameters::LevelDefinition levelDefinition;

  double sqWeight;
  double lgWeight;

  std::string outputFolder;
  bool showIterations;
  bool showProgress;
};

InputData readInput(int argc,char** argv);

}

#endif //BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
