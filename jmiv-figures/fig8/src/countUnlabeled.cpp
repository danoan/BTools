#include "countUnlabeled.h"

CountData countUnlabeled(const InputData& input,
                    const DigitalSet& dsInput)
{
    ODRModel::OptimizationMode optMode;
    if(input.mode==InputData::Concavities)
        optMode = ODRModel::OptimizationMode::OM_CorrectConcavities;
    else
        optMode = ODRModel::OptimizationMode::OM_CorrectConvexities;


    typedef DGtal::Z2i::Point Point;
    typedef DGtal::Z2i::Domain Domain;

    const Domain& domain = dsInput.domain();

    Point size = domain.upperBound() - domain.lowerBound() + Point(1,1);
    cv::Mat cvImage = cv::Mat::zeros(size[1],size[0],CV_8U);
    DIPaCUS::Representation::digitalSetToCVMat(cvImage,dsInput);


    auto odrP = odrPixels(input);
    auto ODR = odrModel(input,optMode,odrP,dsInput);
    auto energyI = energyInput(input,ODR,cvImage);
    SquaredCurvatureTerm sqt(energyI,odrP.handle());


    double ev,evPrior;
    int unlabeled;
    DigitalSet outDS(dsInput.domain());
    LabelsVector labels(sqt.numVars());
    labels.setZero();


    MyQPBOProbeSolver solver(ev,
                             evPrior,
                             unlabeled,
                             sqt.od.localUTM,
                             sqt.od.localTable,
                             labels,
                             10);

    double n = sqt.numVars();
    int pairwiseTerms = sqt.od.localTable.size();
    double pairwisePercentage = pairwiseTerms/( n*(n-1)/2.0 );

    return CountData(unlabeled,
                     pairwiseTerms,
                     unlabeled/(1.0*ODR.optRegion.size()),
                     pairwisePercentage);
}