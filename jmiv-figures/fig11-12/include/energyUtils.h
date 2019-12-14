#ifndef EXPERIMENTS_ENERGYUTILS_H
#define EXPERIMENTS_ENERGYUTILS_H

#include <DGtal/helpers/StdDefs.h>

#include "DIPaCUS/base/Representation.h"

#include "SCaBOliC/Energy/base/EnergyTerm.h"
#include "SCaBOliC/Energy/ISQ/InputData.h"
#include "SCaBOliC/Core/model/ODRModel.h"
#include "SCaBOliC/Core/ODRPixels/ODRPixels.h"

#include "InputData.h"
#include "MockDistribution.h"

typedef SCaBOliC::Energy::EnergyTerm EnergyTerm;
typedef SCaBOliC::Core::ODRModel ODRModel;
typedef SCaBOliC::Core::ODRPixels ODRPixels;
typedef SCaBOliC::Energy::ISQ::InputData EnergyInput;

typedef DGtal::Z2i::DigitalSet DigitalSet;

double sumPairwiseCoefficients(const EnergyTerm& et,unsigned int index);


ODRPixels odrPixels(const InputData& input);

ODRModel odrModel(const InputData& input,
                  const ODRPixels& odrPixels,
                  const DigitalSet& dsInput);


extern MockDistribution fgDistr;
extern MockDistribution bgDistr;
EnergyInput energyInput(const InputData& input, const ODRModel& ODR, const cv::Mat& cvImage);

#endif //EXPERIMENTS_ENERGYUTILS_H
