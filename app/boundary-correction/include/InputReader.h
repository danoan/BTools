#ifndef BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
#define BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include "BTools/core/model/input/ModelParameters.h"


namespace BoundaryCorrection
{
namespace InputReader
{
struct InputData
{
  typedef BTools::Core::ModelParameters ModelParameters;
  typedef ModelParameters::LevelDefinition LevelDefinition;

  InputData();

  int radius;
  int iterations;
  double levels;

  ModelParameters::LevelDefinition levelDefinition;

  double sqWeight;
  double dtWeight;
  double lgWeight;

  std::string grabcutFile;
  int initialDilation;

  std::string outputFolder;
  bool showIterations;
  bool showProgress;
};

InputData readInput(int argc,char** argv);

}
}

#endif //BTOOLS_APPLICATION_INTERACTIVE_INPUTREADER_H
