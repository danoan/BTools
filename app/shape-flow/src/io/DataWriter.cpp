#include "io/DataWriter.h"

using namespace ShapeFlow;

void threadFn(ThreadData& td)
{
    td.IIValue=SCaBOliC::Utils::ISQEvaluation::ii(td.ds,td.h,td.alpha,td.beta,&td.data);
}

void DataWriter::outputElasticaII(const DigitalSet& ds,const double h, const double radius, const double alpha, const double beta, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    ThreadData td(ds,h,radius,alpha,beta);

    std::thread iiEvalThread = std::thread(&threadFn,std::ref(td));
    iiEvalThread.detach();

    int tries=10;
    while(tries>0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
        if(td.IIValue!=-1) break;
        tries--;
    }

    os << fnD(colLength,td.IIValue) << "\t";
}

void DataWriter::outputElasticaMDCA(const DigitalSet& ds,const double h, const double alpha, const double beta, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    double MDCAValue;

    MDCAValue=SCaBOliC::Utils::ISQEvaluation::mdca(ds,h,alpha,beta);

    os << fnD(colLength,MDCAValue) << "\t";
}

double DataWriter::outputShapeArea(const DigitalSet& ds, double gridStep, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    double a = ds.size()*gridStep*gridStep;
    os << fnD(colLength,a) << "\t";

    return a;
}

double DataWriter::outputShapePerimeter(const DigitalSet& ds, const double h, std::ostream& os)
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
    mlpLengthEstimator.init(h,curvePointAdapter.begin(),curvePointAdapter.end(),true);

    perimeter = mlpLengthEstimator.eval();
    os << fnD(colLength,perimeter) << "\t";
    return perimeter;
}

void DataWriter::printTable(const std::string& inputName,const std::vector<TableEntry> &entries, std::ostream &os)
{
    os << "#Image: " << inputName << "\n#\n";
    int colLength=20;

    std::string(*fnS)(int,std::string) = BTools::Utils::fixedStrLength;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    os  << "#" << fnS(colLength,"Iteration") << "\t"
        << fnS(colLength,"Opt. Energy") << "\t"
        << fnS(colLength,"Unlabeled") << "\t"
        << fnS(colLength,"Elastica MDCA") << "\t"
        << fnS(colLength,"Elastica II") << "\t"
        << fnS(colLength,"Perimeter") << "\t"
        << fnS(colLength,"Area") << "\t"
        << fnS(colLength,"Perimeter^2/Area") << "\t"
        << std::endl;

    for(auto it=entries.begin();it!=entries.end();++it)
    {
        if(it->solution.outputDS.size()<10) continue;

        const EnergySolution &curr = (it->solution);
        os << fnS(colLength,it->name) << "\t"
           << fnD(colLength,curr.energyValue) << "\t";
        os << fnD(colLength,curr.unlabeled) << "\t";
        outputElasticaMDCA(it->solution.outputDS,it->gridStep,it->lengthTermWeight,it->sqTermWeight, os);
        outputElasticaII(it->solution.outputDS,it->gridStep,it->radius,it->lengthTermWeight,it->sqTermWeight,os);

        double perimeter = outputShapePerimeter(it->solution.outputDS,it->gridStep,os);
        double area = outputShapeArea(it->solution.outputDS,it->gridStep,os);
        os << fnD(colLength,pow(perimeter,2)/area) << "\t";

        os << "\t\n";
    }
}

void DataWriter::printFlowMetadata(const ModelParameters& modelParameters,
                                   const DigitalSet& dsZero,
                                   std::ofstream &ofs)
{
    ofs << "Levels: " << modelParameters.levels << "("
        << ( (modelParameters.levelDefinition==ModelParameters::LevelDefinition::LD_CloserFromCenter)?"CloserFromCenter":"FartherFromCenter")
        << ")\n";

    ofs << "Radius: " << modelParameters.radius << "\n";
    ofs << "Grid Step: " << modelParameters.gridStep<< "\n";


    ofs << "Squared Curvature Weight: " << modelParameters.sqTermWeight << " \n";
    ofs << "Length Weight: " << modelParameters.lengthTermWeight << " \n";

    ofs << "Initial shape has: " << dsZero.size() << " pixels\n";

}