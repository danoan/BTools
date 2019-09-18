#include "control/DataWriter.h"

using namespace ShapeFlow;

void DataWriter::outputElasticaEnergy(const DigitalSet& ds, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    double IIValue,MDCAValue;

    SCaBOliC::Utils::ISQEvaluation(MDCAValue,ds,
                                   SCaBOliC::Utils::ISQEvaluation::MDCA);

    os << fnD(colLength,MDCAValue) << "\t";
}

void DataWriter::outputShapePerimeter(const DigitalSet& ds, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    double perimeter;

    typedef DIPaCUS::Representation::Image2D Image2D;

    Image2D tempImage(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(tempImage,ds);

    Curve curve;
    DIPaCUS::Misc::computeBoundaryCurve(curve,tempImage,1);

    KSpace kspace;
    kspace.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);

    DGtal::functors::SCellToPoint<KSpace> myFunctor(kspace);

    typedef DGtal::ConstRangeAdapter<Curve::ConstIterator,DGtal::functors::SCellToPoint<KSpace>,Point> MyConstRangeAdapter;
    MyConstRangeAdapter curvePointAdapter(curve.begin(),
                                          curve.end(),
                                          myFunctor);


    DGtal::MLPLengthEstimator<MyConstRangeAdapter::ConstIterator> mlpLengthEstimator;
    mlpLengthEstimator.init(1,curvePointAdapter.begin(),curvePointAdapter.end(),true);

    perimeter = mlpLengthEstimator.eval();

    os << fnD(colLength,perimeter) << "\t";
}

void DataWriter::printTable(const std::string& inputName,const std::vector<TableEntry> &entries, std::ostream &os)
{
    os << "#Image: " << inputName << "\n#\n";
    int colLength=20;

    std::string(*fnS)(int,std::string) = BTools::Utils::fixedStrLength;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    os  << "#" << fnS(colLength,"Iteration") << "\t"
        << fnS(colLength,"Opt. Energy") << "\t"
        << fnS(colLength,"Elastica MDCA") << "\t"
        << fnS(colLength,"Perimeter") << "\t"
        << fnS(colLength,"Unlabeled") << "\t"
        << std::endl;

    for(auto it=entries.begin();it!=entries.end();++it)
    {
        if(it->solution.outputDS.size()==0) continue;

        const EnergySolution &curr = (it->solution);
        os << fnS(colLength,it->name) << "\t"
           << fnD(colLength,curr.energyValue) << "\t";
        outputElasticaEnergy(it->solution.outputDS,os);
        outputShapePerimeter(it->solution.outputDS,os);
        os << fnD(colLength,curr.unlabeled) << "\t\n";
    }
}

void DataWriter::printFlowMetadata(const BCConfigInput& bcInput,
                                   const ODRConfigInput& odrConfigInput,
                                    const DigitalSet& dsZero,
                                    std::ofstream &ofs)
{
    ofs << "Levels: " << odrConfigInput.levels << "("
        << ( (odrConfigInput.levelDefinition==ODRConfigInput::LevelDefinition::LD_CloserFromCenter)?"CloserFromCenter":"FartherFromCenter")
        << ")\n";

    ofs << "Radius: " << bcInput.radius << "\n";

    if( odrConfigInput.neighborhood==ODRConfigInput::NeighborhoodType::FourNeighborhood ) ofs << "Neighborhood: 4\n";
    if( odrConfigInput.neighborhood==ODRConfigInput::NeighborhoodType::EightNeighborhood ) ofs << "Neighborhood: 8\n";


    ofs << "Squared Curvature Weight: " << bcInput.sqTermWeight << " \n";
    ofs << "Length Weight: " << bcInput.lengthTermWeight << " \n";
    ofs << "Data Weight: " << bcInput.dataTermWeight << " \n";

    ofs << "Opt region in application: " << odrConfigInput.optInApplicationRegion << "\n";
    ofs << "Initial shape has: " << dsZero.size() << " pixels\n";



}