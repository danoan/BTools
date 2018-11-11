#include "ElasticaProblem/ElasticaProblem.h"

using namespace BTools::Application::Illustration;

void ElasticaProblem::createAndSaveDS(const RealPoint& A,
                                      const RealPoint& B,
                                      const RealPoint& tA,
                                      const RealPoint& tB,
                                      const std::string& filename)
{
    DGtal::Board2D board;
    ElasticaInput e0(A, B, tA, tB);

    board << e0.inputDS.domain() << e0.inputDS;
    board.saveEPS(filename.c_str());
}

void ElasticaProblem::testElasticaInput()
{

    Point A(0,0);
    Point B(100,0);

    RealPoint piOverFour(sqrt(2) / 2, sqrt(2) / 2);
    RealPoint threePiOverFour(sqrt(2) / 2, -sqrt(2) / 2);

    createAndSaveDS(A,B,piOverFour,piOverFour,"elasticaDS-0.eps");
    createAndSaveDS(A,B,piOverFour, threePiOverFour,"elasticaDS-1.eps");
    createAndSaveDS(A,B,threePiOverFour, piOverFour,"elasticaDS-2.eps");
    createAndSaveDS(A,B,threePiOverFour, threePiOverFour,"elasticaDS-3.eps");

}

void ElasticaProblem::example()
{
    Point A(0,0);
    Point B(100,0);

    RealPoint piOverFour(sqrt(2) / 2, sqrt(2) / 2);
    RealPoint threePiOverFour(sqrt(2) / 2, -sqrt(2) / 2);

//    ElasticaInput ei(A,B,threePiOverFour,piOverFour);
    ElasticaInput ei(A,B,threePiOverFour,threePiOverFour);
//    ElasticaInput ei(A,B,piOverFour, threePiOverFour);

    unsigned int radius =3;
    int iterations=10;
    DigitalSet inputDS = ei.inputDS;
    for(int i=0;i<iterations;++i)
    {
        IterationData ID = nextIterationData(i);
        ODRModel ODR = createODR(ei,
                                 inputDS,
                                 ID.optMode,
                                 ID.appMode,
                                 radius);

        SCaBOliC::Core::Display::DisplayODR(ODR,"ODR.eps");

        Solution solution = boundaryCorrection(ODR,
                                               ID.optMode,
                                               ID.appMode,
                                               radius);

        DGtal::Board2D board;
        board << solution.outputDS.domain() << solution.outputDS;
        board.saveEPS("solution.eps");

        inputDS.clear();
        inputDS.insert(solution.outputDS.begin(),solution.outputDS.end());

        solution.outputDS.erase(ei.A);
        solution.outputDS.erase(ei.B);
        SCaBOliC::Core::Display::DisplayModifiedBoundary(ODR,solution.outputDS,"modified-boundary.eps");
    }

}

ElasticaProblem::IterationData ElasticaProblem::nextIterationData(const int iteration)
{
    if(iteration%2==0) return IterationData(OptimizationMode::OM_OriginalBoundary,ApplicationMode::AM_AroundBoundary);
    else return IterationData(OptimizationMode::OM_DilationBoundary,ApplicationMode::AM_InverseAroundBoundary);
}

ElasticaProblem::Solution ElasticaProblem::boundaryCorrection(const ODRModel& ODR,
                                                              const OptimizationMode& optMode,
                                                              const ApplicationMode& appMode,
                                                              const unsigned int radius)
{
    typedef DIPaCUS::Representation::Image2D Image2D;

    Point dimSize = ODR.domain.upperBound() - ODR.domain.lowerBound() + Point(1,1);
    cv::Mat mockImage(dimSize(1),dimSize(0),CV_8UC3);
    MockDistribution fgDistr;
    MockDistribution bgDistr;

    ISQInputData energyInput(ODR,
                             mockImage,
                             radius,
                             fgDistr,
                             bgDistr,
                             0,
                             1.0,
                             0,
                             Point(0,0));

    ODRPixels odrFactory(ApplicationCenter::AC_PIXEL,
                         CountingMode::CM_PIXEL,
                         energyInput.radius);

    ISQEnergy energy(energyInput,odrFactory.handle());
    Solution solution(ODR.domain);
    solution.init(energy.numVars());

    solution.labelsVector.setZero();
    energy.template solve<QPBOProbeSolver>(solution);

    updateSet(solution,odrFactory,appMode,energyInput,energy);

    return solution;
}

void ElasticaProblem::updateSet(Solution& solution,
                                const ODRInterface& odrFactory,
                                const ApplicationMode& appMode,
                                const ISQInputData& energyInput,
                                const ISQEnergy& energy)
{
    DigitalSet initialDS(energyInput.optimizationRegions.domain);
    DigitalSet tempOutDS(energyInput.optimizationRegions.domain);

    const DigitalSet& optRegion = energyInput.optimizationRegions.optRegion;
    Solution::LabelsVector labelsVector = solution.labelsVector;

    if(appMode==ApplicationMode::AM_InverseAroundBoundary)
    {
        //Invert Solution
        for (int i = 0; i < labelsVector.rows(); ++i)
        {
            labelsVector.coeffRef(i) = 1-labelsVector.coeff(i);
        }
        initialDS.insert(energyInput.optimizationRegions.trustBKG.begin(),
                         energyInput.optimizationRegions.trustBKG.end());
    }else
    {
        initialDS.insert(energyInput.optimizationRegions.trustFRG.begin(),
                         energyInput.optimizationRegions.trustFRG.end());
    }


    odrFactory.handle()->solutionSet(tempOutDS,
                                    initialDS,
                                    energyInput.optimizationRegions,
                                    labelsVector.data(),
                                    energy.vm().pim);

    solution.outputDS.clear();
    solution.outputDS.insert(tempOutDS.begin(),tempOutDS.end());
}

ElasticaProblem::DigitalSet ElasticaProblem::aroundBoundary(const DigitalSet& optRegionDS,
                                                            const ElasticaInput& ei,
                                                            unsigned int length)
{
    DigitalSet output(optRegionDS.domain());
    for(int i=1;i<=length;++i)
    {
        for(auto it=optRegionDS.begin();it!=optRegionDS.end();++it)
        {
            output.insert( *it + i*Point(0,1) );
            output.insert( *it - i*Point(0,1) );

            output.insert(ei.A + i*Point(0,1));
            output.insert(ei.A - i*Point(0,1));

            output.insert(ei.B + i*Point(0,1));
            output.insert(ei.B - i*Point(0,1));
        }
    }

    return output;
}

ElasticaProblem::ODRModel ElasticaProblem::createODR(const ElasticaInput& ei,
                                                     const DigitalSet& inputDS,
                                                     const OptimizationMode& optMode,
                                                     const ApplicationMode& appMode,
                                                     unsigned int radius)
{
    const DigitalSet& original = inputDS;

    Domain domain(original.domain().lowerBound() - 2*Point(radius,radius),
                  original.domain().upperBound() + 2*Point(radius,radius));

    DigitalSet optRegionDS(domain);
    DigitalSet appRegionDS(domain);


    optRegionDS = optRegion(ei,inputDS,optMode);


    switch (appMode)
    {
        case ApplicationMode::AM_AroundBoundary: {
//            DigitalSet temp = SCaBOliC::Core::ODRPixels::amAroundBoundary(original,optRegionDS,radius);
            DigitalSet temp = aroundBoundary(optRegionDS,ei,2);
            appRegionDS.insert(temp.begin(),temp.end());
            break;
        }
        case ApplicationMode::AM_InverseAroundBoundary: {
//            DigitalSet temp = SCaBOliC::Core::ODRPixels::amAroundBoundary(original,optRegionDS,radius);
            DigitalSet temp = aroundBoundary(optRegionDS,ei,2);
            appRegionDS.insert(temp.begin(),temp.end());
            break;
        }
    }

    for(int i=1;i<5;++i)
    {
        optRegionDS.erase(ei.A+Point(0,1)*i);
        optRegionDS.erase(ei.B+Point(0,1)*i);
    }

    DigitalSet extendedOriginal(original.domain());
    extendedOriginal.insert(original.begin(),original.end());
    extendedOriginal.insert(optRegionDS.begin(),optRegionDS.end());

    DigitalSet trustFRG(domain);
    DIPaCUS::SetOperations::setDifference(trustFRG, extendedOriginal, optRegionDS);

//    if(optMode==OptimizationMode::OM_DilationBoundary)
//    {
//        DigitalSet isolatedDS = SCaBOliC::Core::ODRPixels::isolatedPoints(original,optRegionDS);
//        trustFRG+=isolatedDS;
//    }

    DigitalSet trustBKG(domain);
    DigitalSet tempp(domain);

    tempp += trustFRG;
    tempp += optRegionDS;




    trustBKG.assignFromComplement(tempp);


    if(appMode==ApplicationMode::AM_InverseAroundBoundary)
    {
        DigitalSet swap = trustFRG;
        trustFRG = trustBKG;
        trustBKG = swap;
    }

    return ODRModel(domain,
                    original,
                    optRegionDS,
                    trustFRG,
                    trustBKG,
                    appRegionDS,
                    [](Point p){ return p; });


}

ElasticaProblem::DigitalSet ElasticaProblem::optRegion(const ElasticaInput &ei,
                                                       const DigitalSet& inputDS,
                                                       const OptimizationMode& optMode)
{
    typedef DIPaCUS::Representation::Image2D Image2D;

    Image2D imageDS(inputDS.domain());
    DIPaCUS::Representation::digitalSetToImage(imageDS,inputDS);

    Curve curve;
    DIPaCUS::Misc::ComputeBoundaryCurve(imageDS,curve,1);

    Point A = ei.A;
    Point B = ei.B;

    Curve segCurve = curveSegment(curve,A,B);

    DGtal::Board2D board;
    board << imageDS.domain() << segCurve;
    board.saveEPS("segCurve.eps");

    DigitalSet segCurveDS(inputDS.domain());
    if(optMode==OptimizationMode::OM_OriginalBoundary)
        segCurveDS = digitalSetFromCurve(segCurve,true);
    else
        segCurveDS = digitalSetFromCurve(segCurve,false);

    board.clear();
    board << segCurveDS.domain() << segCurveDS;
    board.saveEPS("segCurveDS.eps");


    return segCurveDS;

}

bool ElasticaProblem::adjacentLinel(const Curve::SCell &linel,
                                    const KSpace& KCurve,
                                    const Point &pixelSpacePoint)
{
    const Point& A = pixelSpacePoint;

    KSpace::SCells pixels =  KCurve.sUpperIncident(linel);
    for(auto p=pixels.begin();p!=pixels.end();++p)
    {
        Point pixelSpaceCoord = (p->preCell().coordinates - Point(1,1))/2;
        if ( A(0)==pixelSpaceCoord(0) && A(1)==pixelSpaceCoord(1) ) return true;
    }

    return false;


}

ElasticaProblem::Curve ElasticaProblem::curveSegment(const Curve &curve,
                                                     const Point &leftMost,
                                                     const Point &rightMost)
{
    typedef DGtal::Z2i::KSpace KSpace;

    DIPaCUS::Properties::BoundingBox bb;
    DIPaCUS::Properties::curveBoundingBox(bb,curve.begin(),curve.end());    //counterclockwise curve

    KSpace KCurve;
    KCurve.init(bb.lb,bb.ub,true);

    Curve::ConstIterator begin = curve.begin();
    Curve::ConstIterator end = curve.end();


    typedef DGtal::Circulator<Curve::ConstIterator> CurveCirculator;
    CurveCirculator curveCirc(begin,begin,end);

    CurveCirculator it = curveCirc;
    do
    {
        if( adjacentLinel(*it,KCurve,rightMost) )
        {
            break;
        }
        ++it;
    }while(it!=curveCirc);

    while(adjacentLinel(*it,KCurve,rightMost)) ++it;

    Curve segCurve;
    while( !adjacentLinel(*it,KCurve,leftMost) )
    {
        segCurve.push_back(*it);
        ++it;
    }

    return segCurve;
}

ElasticaProblem::DigitalSet ElasticaProblem::digitalSetFromCurve(const Curve &curve,
                                                                 bool directIncident)
{
    DIPaCUS::Properties::BoundingBox bb;
    DIPaCUS::Properties::curveBoundingBox(bb,curve.begin(),curve.end());

    Domain domain(bb.lb - Point(1,1),bb.ub + Point(1,1));

    KSpace KCurve;
    KCurve.init(domain.lowerBound(),domain.upperBound(),true);

    DigitalSet ds( domain );
    for(auto it=curve.begin();it!=curve.end();++it)
    {
        if(directIncident)
        {
            Curve::SCell sc = KCurve.sDirectIncident(*it, KCurve.sOrthDir(*it));
            ds.insert( (sc.preCell().coordinates - Point(1,1) )/2 );
        }
        else
        {
            Curve::SCell sc = KCurve.sIndirectIncident(*it, KCurve.sOrthDir(*it));
            ds.insert( (sc.preCell().coordinates - Point(1,1) )/2 );
        }
    }

    return ds;
}