#ifndef EXPERIMENTS_PROBESOLVER_H
#define EXPERIMENTS_PROBESOLVER_H

#include <DGtal/helpers/StdDefs.h>

#include "SCaBOliC/Core/model/ODRModel.h"
#include "SCaBOliC/Optimization/solver/probe/QPBOProbeSolver.h"
#include "SCaBOliC/Optimization/solver/simple/QPBOSimpleSolver.h"

#include "SCaBOliC/Energy/ISQ/Terms/SquaredCurvature/SquaredCurvatureTerm.h"
#include "SCaBOliC/Energy/model/OptimizationData.h"
#include "SCaBOliC/Energy/model/Solution.h"

#include "InputData.h"
#include "energyUtils.h"

typedef DGtal::Z2i::DigitalSet DigitalSet;

typedef SCaBOliC::Core::ODRModel ODRModel;

typedef SCaBOliC::Energy::OptimizationData::UnaryTermsMatrix UnaryTermsMatrix;
typedef SCaBOliC::Energy::OptimizationData::PairwiseTermsMatrix PairwiseTermsMatrix;
typedef SCaBOliC::Energy::OptimizationData::EnergyTable EnergyTable;
typedef SCaBOliC::Energy::Solution::LabelsVector LabelsVector;
typedef SCaBOliC::Energy::ISQ::SquaredCurvatureTerm SquaredCurvatureTerm;

struct CountData
{
    CountData(int unlabeled,
              int pairwiseTerns,
              double unlabeledPercentage,
              double pairwisePercentage):unlabeled(unlabeled),
                                         pairwiseTerms(pairwiseTerms),
                                         unlabeledPercentage(unlabeledPercentage),
                                         pairwisePercentage(pairwisePercentage){}

    int unlabeled;
    int pairwiseTerms;
    double pairwisePercentage;
    double unlabeledPercentage;
};

typedef QPBOProbeSolver<UnaryTermsMatrix,
EnergyTable,
LabelsVector> MyQPBOProbeSolver;

typedef QPBOSimpleSolver<UnaryTermsMatrix,
        EnergyTable,
        LabelsVector> MyQPBOSimpleSolver;

CountData countUnlabeled(const InputData& input,
                    const DigitalSet& dsInput);

#endif //EXPERIMENTS_PROBESOLVER_H
