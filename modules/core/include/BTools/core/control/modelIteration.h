#ifndef BTools_CORE_MODEL_ITERATION_H
#define BTools_CORE_MODEL_ITERATION_H

#include <opencv2/core/mat.hpp>

#include <DIPaCUS/base/Representation.h>

#include <SCaBOliC/Core/interface/ODRInterface.h>
#include <SCaBOliC/Energy/model/Solution.h>
#include <SCaBOliC/Energy/ISQ/ISQEnergy.h>

#include "BTools/core/model/input/BCInput.h"
#include "BTools/utils/imgUtils.h"

namespace BTools{
namespace Core{
typedef DIPaCUS::Representation::DigitalSet DigitalSet;

typedef SCaBOliC::Core::ODRInterface ODRInterface;
typedef SCaBOliC::Energy::ISQ::InputData ISQInputData;
typedef SCaBOliC::Energy::ISQEnergy ISQEnergy;
typedef SCaBOliC::Energy::Solution Solution;

typedef BTools::Core::ImageData ImageData;
typedef BTools::Core::BCInput BCInput;


void solveModel(Solution& solution,
                const BCInput& bcInput,
                const ODRInterface& odrFactory,
                const DigitalSet& inputDS);

void updateSet(Solution& solution,
               const ODRInterface& odrFactory,
               const ISQInputData& energyInput,
               const ISQEnergy& energy);

cv::Mat createBCImage(const DigitalSet& outputDS, const ImageData& imageData);
}
}

#endif //BTools_CORE_MODEL_ITERATION_H
