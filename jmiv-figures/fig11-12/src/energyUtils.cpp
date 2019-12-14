#include "energyUtils.h"

MockDistribution fgDistr;
MockDistribution bgDistr;

double sumPairwiseCoefficients(const EnergyTerm& et,unsigned int index)
{
    double s = et.od.localPTM.row(index).sum();
    s += et.od.localPTM.col(index).sum();

    return s;
}

ODRPixels odrPixels(const InputData& input)
{
    return     ODRPixels ( input.radius,
                           input.gridStep,
                           input.levels,
                           input.ld,
                           ODRModel::NeighborhoodType::FourNeighborhood);
}

ODRModel odrModel(const InputData& input,
                  const ODRModel::OptimizationMode& optMode,
                  const ODRPixels& odrPixels,
                  const DigitalSet& dsInput)
{
    return odrPixels.createODR(optMode,
                                       ODRModel::ApplicationMode::AM_AroundBoundary,
                                       dsInput,
                                       input.optInApplication);
}

EnergyInput energyInput(const InputData& input, const ODRModel& ODR, const cv::Mat& cvImage)
{
    return     EnergyInput (ODR,
                              cvImage,
                              fgDistr,
                              bgDistr,
                              input.excludeOptPointsFromAreaComputation,
                              true,
                              0,
                              input.sqTermWeight,
                              0);
}