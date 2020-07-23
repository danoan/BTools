#ifndef BTOOLS_APPLICATION_REGIONS_OF_INTEREST_INPUTREADER_H
#define BTOOLS_APPLICATION_REGIONS_OF_INTEREST_INPUTREADER_H

#include <iostream>
#include <unistd.h>

#include <BTools/core/model/input/ModelParameters.h>
#include <BTools/core/model/ShapeType.h>


namespace RegionsOfInterest{
struct InputData
{
  typedef BTools::Core::ModelParameters ModelParameters;
  typedef ModelParameters::LevelDefinition LevelDefinition;
  typedef BTools::Core::Shape Shape;
  typedef BTools::Core::ShapeType ShapeType;

  InputData();

  Shape shape;
  double gridStep;

  int radius;
  double levels;
  int optBand;

  ModelParameters::LevelDefinition levelDefinition;
  std::string outputFilepath;
};

InputData readInput(int argc,char** argv);

}

#endif //BTOOLS_APPLICATION_REGIONS_OF_INTEREST_INPUTREADER_H
