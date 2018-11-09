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
    SCaBOliC::Utils::IIISQEvaluation(IIValue,ds);
    SCaBOliC::Utils::MDCAISQEvaluation(MDCAValue,ds);

    os << fnD(colLength,IIValue) << "\t"
       << fnD(colLength,MDCAValue) << "\t";
}


void FlowControl::printTable(const std::vector<TableEntry> &entries, std::ostream &os)
{
    int colLength=20;

    std::string(*fnS)(int,std::string) = BTools::Utils::fixedStrLength;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    os  << fnS(colLength,"Iteration") << "\t"
        << fnS(colLength,"Opt. Energy") << "\t"
        << fnS(colLength,"Elastica II") << "\t"
        << fnS(colLength,"Elastica MDCA") << "\t"
        << fnS(colLength,"Unlabeled") << "\t"
        << std::endl;

    for(auto it=entries.begin();it!=entries.end();++it)
    {
        const Solution &curr = (it->solution);
        os << fnS(colLength,it->name) << "\t"
           << fnD(colLength,curr.energyValue) << "\t";
        outputElasticaEnergy(it->solution.outputDS,os);
        os << fnD(colLength,curr.unlabeled) << "\t\n";
    }
}

FlowControl::FlowControl(const BCFlowInput& bcFLowInput,
                         const std::string& outputFolder,
                         bool exportRegions)
{
    boost::filesystem::create_directories(outputFolder);
    std::ofstream ofs(outputFolder + "/input-data.txt");

    if( bcFLowInput.flowConfigInput.flowProfile==FlowConfigInput::FlowProfile::SingleStep ) ofs << "Flow Profile: Single Step \n";
    if( bcFLowInput.flowConfigInput.flowProfile==FlowConfigInput::FlowProfile::DoubleStep) ofs << "Flow Profile: Double Step \n";
    if( bcFLowInput.flowConfigInput.applicationCenter==FlowConfigInput::ApplicationCenter::AC_PIXEL) ofs << "Application Center: Pixel \n";
    if( bcFLowInput.flowConfigInput.applicationCenter==FlowConfigInput::ApplicationCenter::AC_POINTEL) ofs << "Application Center: Pointel \n";
    if( bcFLowInput.flowConfigInput.countingMode==FlowConfigInput::CountingMode::CM_PIXEL) ofs << "Counting Mode: Pixel \n";
    if( bcFLowInput.flowConfigInput.countingMode==FlowConfigInput::CountingMode::CM_POINTEL) ofs << "Counting Mode: Pointel \n";
    if( bcFLowInput.flowConfigInput.spaceMode==FlowConfigInput::SpaceMode::Pixel) ofs << "Space Mode: Pixel \n";
    if( bcFLowInput.flowConfigInput.spaceMode==FlowConfigInput::SpaceMode::Interpixel) ofs << "Space Mode: Interpixel \n";

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
