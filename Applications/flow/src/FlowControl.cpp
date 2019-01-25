#include "FlowControl.h"

using namespace BTools::Application::Flow;
using namespace BTools::Application;


void FlowControl::exportImageFromDigitalSet(const DigitalSet& ds,
                                            const std::string& outputFilepath)
{
    DGtal::Z2i::Point lb,ub;
    ds.computeBoundingBox(lb,ub);
    lb+=DGtal::Z2i::Point(-80,-80);
    ub+=DGtal::Z2i::Point(80,80);
    Image2D image( DGtal::Z2i::Domain(lb,ub) );
    DIPaCUS::Representation::digitalSetToImage(image, ds);

    DGtal::GenericWriter<Image2D>::exportFile(outputFilepath, image);
}

void FlowControl::exportImageFromDigitalSet(const DigitalSet& ds,
                                            const Domain& domain,
                                            const std::string& outputFilepath)
{

    Image2D image( domain );
    DIPaCUS::Representation::digitalSetToImage(image, ds);

    DGtal::GenericWriter<Image2D>::exportFile(outputFilepath, image);
}

void FlowControl::outputElasticaEnergy(const DigitalSet& ds, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = Utils::fixedStrLength;

    double IIValue,MDCAValue;
    SCaBOliC::Utils::ISQEvaluation(IIValue,ds,
                                   SCaBOliC::Utils::ISQEvaluation::II);

    SCaBOliC::Utils::ISQEvaluation(MDCAValue,ds,
                                   SCaBOliC::Utils::ISQEvaluation::MDCA);

    os << fnD(colLength,IIValue) << "\t"
       << fnD(colLength,MDCAValue) << "\t";
}

void FlowControl::outputShapePerimeter(const DigitalSet& ds, std::ostream& os)
{
    int colLength=20;
    std::string(*fnD)(int,double) = Utils::fixedStrLength;

    double perimeter;

    typedef DIPaCUS::Representation::Image2D Image2D;

    Image2D tempImage(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(tempImage,ds);

    Curve curve;
    DIPaCUS::Misc::ComputeBoundaryCurve(tempImage,curve,1);

    KSpace kspace;
    kspace.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);


    typedef DGtal::ConstRangeAdapter<Curve::ConstIterator,DGtal::functors::SCellToPoint<KSpace>,Point> MyConstRangeAdapter;
    MyConstRangeAdapter curvePointAdapter(curve.begin(),
                                          curve.end(),
                                          DGtal::functors::SCellToPoint<KSpace>(kspace));


    DGtal::MLPLengthEstimator<MyConstRangeAdapter::ConstIterator> mlpLengthEstimator;
    mlpLengthEstimator.init(1,curvePointAdapter.begin(),curvePointAdapter.end(),true);

    perimeter = mlpLengthEstimator.eval();

    os << fnD(colLength,perimeter) << "\t";
}


void FlowControl::printTable(const std::vector<TableEntry> &entries, std::ostream &os)
{
    int colLength=20;

    std::string(*fnS)(int,std::string) = BTools::Utils::fixedStrLength;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    os  << "#" << fnS(colLength,"Iteration") << "\t"
        << fnS(colLength,"Opt. Energy") << "\t"
        << fnS(colLength,"Elastica II") << "\t"
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

FlowControl::FlowControl(const BCFlowInput& bcFLowInput,
                         const std::string& outputFolder,
                         bool exportRegions)
{

    boost::filesystem::create_directories(outputFolder);
    std::ofstream ofs(outputFolder + "/input-data.txt");

    printFlowMetadata(bcFLowInput,ofs);
    ofs.flush();
    ofs.close();

    double r=40;
    double h=1.0;

    Ball ball(0,0,r);
    Flower flower(0,0,r,20,2,1);
    NGon triangle(0,0,r,3,1);
    NGon square(0,0,r,4,3.1415/4.0);
    NGon pentagon(0,0,r,5,1);
    NGon heptagon(0,0,r,7,1);
    Ellipse ellipse(0,0,r,r-10,0);

    shapeFlow(ball,bcFLowInput,h,"Ball",outputFolder,exportRegions);
    shapeFlow(flower,bcFLowInput,h,"Flower",outputFolder,exportRegions);
    shapeFlow(triangle,bcFLowInput,h,"Triangle",outputFolder,exportRegions);
    shapeFlow(square,bcFLowInput,h,"Square",outputFolder,exportRegions);
    shapeFlow(pentagon,bcFLowInput,h,"Pentagon",outputFolder,exportRegions);
    shapeFlow(heptagon,bcFLowInput,h,"Heptagon",outputFolder,exportRegions);
    shapeFlow(ellipse,bcFLowInput,h,"Ellipse",outputFolder,exportRegions);
}

void FlowControl::printFlowMetadata(const BCFlowInput &bcFlowInput,
                                    std::ofstream &ofs)
{
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::SingleStep ) ofs << "Flow Profile: Single Step \n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::SingleStepOpt ) ofs << "Flow Profile: Single Step Opt \n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::DoubleStep) ofs << "Flow Profile: Double Step \n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::DoubleStepOpt) ofs << "Flow Profile: Double Step Opt\n";

    if( bcFlowInput.odrConfigInput.applicationCenter==BCFlowInput::ODRConfigInput::ApplicationCenter::AC_PIXEL) ofs << "Application Center: Pixel \n";
    if( bcFlowInput.odrConfigInput.applicationCenter==BCFlowInput::ODRConfigInput::ApplicationCenter::AC_POINTEL) ofs << "Application Center: Pointel \n";
    if( bcFlowInput.odrConfigInput.applicationCenter==BCFlowInput::ODRConfigInput::ApplicationCenter::AC_LINEL) ofs << "Application Center: Linel \n";

    if( bcFlowInput.odrConfigInput.countingMode==BCFlowInput::ODRConfigInput::CountingMode::CM_PIXEL) ofs << "Counting Mode: Pixel \n";
    if( bcFlowInput.odrConfigInput.countingMode==BCFlowInput::ODRConfigInput::CountingMode::CM_POINTEL) ofs << "Counting Mode: Pointel \n";

    if( bcFlowInput.odrConfigInput.spaceMode==BCFlowInput::ODRConfigInput::SpaceMode::Pixel) ofs << "Space Mode: Pixel \n";
    if( bcFlowInput.odrConfigInput.spaceMode==BCFlowInput::ODRConfigInput::SpaceMode::Interpixel) ofs << "Space Mode: Interpixel \n";

    ofs << "Levels: " << bcFlowInput.odrConfigInput.levels << "\n";

    if( bcFlowInput.odrConfigInput.neighborhood==BCFlowInput::ODRConfigInput::NeighborhoodType::FourNeighborhood ) ofs << "Neighborhood: 4\n";
    if( bcFlowInput.odrConfigInput.neighborhood==BCFlowInput::ODRConfigInput::NeighborhoodType::EightNeighborhood ) ofs << "Neighborhood: 8\n";



}
