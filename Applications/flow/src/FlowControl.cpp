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
//    SCaBOliC::Utils::ISQEvaluation(IIValue,ds,
//                                   SCaBOliC::Utils::ISQEvaluation::II);

    SCaBOliC::Utils::ISQEvaluation(MDCAValue,ds,
                                   SCaBOliC::Utils::ISQEvaluation::MDCA);

//    os << fnD(colLength,IIValue) << "\t"
      os << fnD(colLength,MDCAValue) << "\t";
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


void FlowControl::printTable(const std::vector<TableEntry> &entries, std::ostream &os)
{
    int colLength=20;

    std::string(*fnS)(int,std::string) = BTools::Utils::fixedStrLength;
    std::string(*fnD)(int,double) = BTools::Utils::fixedStrLength;

    os  << "#" << fnS(colLength,"Iteration") << "\t"
        << fnS(colLength,"Opt. Energy") << "\t"
//        << fnS(colLength,"Elastica II") << "\t"
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

    Bone bone(Bone::Domain(Bone::Point(0,0),Bone::Point(300,150)));
    Bone flag(Bone::Domain(Bone::Point(0,0),Bone::Point(200,150)));
    std::string boneImgPath = PROJECT_DIR;
    std::string flagImgPath = PROJECT_DIR;
    boneImgPath += "/images/dataset/bone.pgm";
    flagImgPath += "/images/dataset/flag.pgm";
    DIPaCUS::Representation::imageAsDigitalSet(bone,boneImgPath);
    //DIPaCUS::Representation::imageAsDigitalSet(flag,flagImgPath);

//    shapeFlow( digitizeShape(ball,h),bcFLowInput,"Ball",outputFolder,exportRegions);
    shapeFlow( digitizeShape(flower,h),bcFLowInput,"Flower",outputFolder,exportRegions);
//    shapeFlow( digitizeShape(triangle,h),bcFLowInput,"Triangle",outputFolder,exportRegions);
//    shapeFlow( digitizeShape(square,h),bcFLowInput,"Square",outputFolder,exportRegions);
//    shapeFlow(bone,bcFLowInput,"Bone",outputFolder,exportRegions);
//    shapeFlow(flag,bcFLowInput,"Flag",outputFolder,exportRegions);
//    shapeFlow( digitizeShape(pentagon,h),bcFLowInput,"Pentagon",outputFolder,exportRegions);
//    shapeFlow( digitizeShape(heptagon,h),bcFLowInput,"Heptagon",outputFolder,exportRegions);
//    shapeFlow( digitizeShape(ellipse,h),bcFLowInput,"Ellipse",outputFolder,exportRegions);
}


void FlowControl::shapeFlow(const DigitalSet& _ds,
                            const BCFlowInput& bcFlowInput,
                            std::string imageName,
                            std::string outputFolder,
                            bool exportRegions)
{
    std::cerr << "Flow Start: " << imageName << "\n";
    std::cerr << "Iterations (" << bcFlowInput.maxIterations << "): ";

    std::string flowFolder = outputFolder
                             + "/" + imageName;
    boost::filesystem::create_directories(flowFolder);
    std::ofstream os(outputFolder + "/" + imageName + ".txt");


    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));
    Domain flowDomain = ds.domain();

    std::string currImagePath = flowFolder + "/" + BTools::Utils::nDigitsString(0,4) + ".pgm";
    exportImageFromDigitalSet(ds,flowDomain,currImagePath);

    os << "#Image: " << imageName << "\n#\n";

    cv::Mat img = cv::imread(currImagePath,cv::IMREAD_COLOR);
    Domain solutionDomain(Point(0,0),Point(img.cols-1,img.rows-1));


    MockDistribution frDistr;
    MockDistribution bkDistr;

    std::vector<TableEntry> entries;

    BCAOutput::EnergySolution firstSolution(ds.domain());
    firstSolution.outputDS = ds;
    firstSolution.energyValue = -1;
    entries.push_back(TableEntry(firstSolution,"0"));

    int i=1;
    do
    {
        std::cerr << "|";

        std::vector<IBCControlVisitor*> visitors;
        visitors.push_back(new Flow::PotentialMap(flowFolder + "/" + BTools::Utils::nDigitsString(i,4) + "-pm.eps") );

        cv::Mat imgTT = cv::imread(currImagePath,cv::IMREAD_COLOR);

        try
        {
            ImageDataInput imageDataInput(frDistr,
                                          bkDistr,
                                          imgTT,
                                          imgTT);

            BCAInput bcaInput(bcFlowInput.bcInput,
                              imageDataInput,
                              bcFlowInput.odrConfigInput,
                              bcFlowInput.flowProfile);

            BCAOutput bcaOutput(bcaInput);

            BinOCS::BoundaryCorrection::BCApplication BCA(bcaOutput,
                                                          bcaInput,
                                                          1);



            entries.push_back(TableEntry(bcaOutput.energySolution,std::to_string(i)));

            currImagePath = flowFolder + "/" + BTools::Utils::nDigitsString(i,4) + ".pgm";

            const BCAOutput::EnergySolution& solution = bcaOutput.energySolution;
            DigitalSet translatedBackDS( Domain( Point(0,0),
                                                 Point(imgTT.cols-1,imgTT.rows-1)
            ) );

            for (auto it = solution.outputDS.begin(); it != solution.outputDS.end(); ++it)
            {
                translatedBackDS.insert(*it + imageDataInput.translation );
            }


            Point lb,ub;
            translatedBackDS.computeBoundingBox(lb,ub);

            if(lb(0) <= flowDomain.lowerBound()(0)+1 ||
               lb(1) <= flowDomain.lowerBound()(1)+1 ||
               ub(0) >= flowDomain.upperBound()(0)-1 ||
               ub(1) >= flowDomain.upperBound()(1)-1 )
            {
                throw std::runtime_error("Result image is too big.");
            }

            if(translatedBackDS.size()<10) throw std::runtime_error("Result image is too small.");


            exportImageFromDigitalSet(translatedBackDS,flowDomain,currImagePath);
        }catch(std::exception ex)
        {
            std::cerr << ex.what();
            break;
        }

        ++i;
        delete visitors[0];
    }while(i<bcFlowInput.maxIterations);


    std::cerr << "\nWriting Results...";
    printTable(entries,os);
    std::cerr << "\n\n";

}

void FlowControl::printFlowMetadata(const BCFlowInput &bcFlowInput,
                                    std::ofstream &ofs)
{
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::SingleStep ) ofs << "Flow Profile: Single Step \n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::SingleStepOpt ) ofs << "Flow Profile: Single Step Opt \n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::DoubleStep) ofs << "Flow Profile: Double Step \n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::DoubleStepOpt) ofs << "Flow Profile: Double Step Opt\n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::SingleStepInner) ofs << "Flow Profile: Single Step Inner\n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::DoubleStepInner) ofs << "Flow Profile: Double Step Inner\n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::SingleStepAroundInner) ofs << "Flow Profile: Single Step Single-Inner\n";
    if( bcFlowInput.flowProfile==BCFlowInput::FlowProfile::DoubleStepAroundInner) ofs << "Flow Profile: Double Step Around-Inner\n";

    if( bcFlowInput.odrConfigInput.applicationCenter==BCFlowInput::ODRConfigInput::ApplicationCenter::AC_PIXEL) ofs << "Application Center: Pixel \n";
    if( bcFlowInput.odrConfigInput.applicationCenter==BCFlowInput::ODRConfigInput::ApplicationCenter::AC_POINTEL) ofs << "Application Center: Pointel \n";
    if( bcFlowInput.odrConfigInput.applicationCenter==BCFlowInput::ODRConfigInput::ApplicationCenter::AC_LINEL) ofs << "Application Center: Linel \n";

    if( bcFlowInput.odrConfigInput.countingMode==BCFlowInput::ODRConfigInput::CountingMode::CM_PIXEL) ofs << "Counting Mode: Pixel \n";
    if( bcFlowInput.odrConfigInput.countingMode==BCFlowInput::ODRConfigInput::CountingMode::CM_POINTEL) ofs << "Counting Mode: Pointel \n";

    if( bcFlowInput.odrConfigInput.spaceMode==BCFlowInput::ODRConfigInput::SpaceMode::Pixel) ofs << "Space Mode: Pixel \n";
    if( bcFlowInput.odrConfigInput.spaceMode==BCFlowInput::ODRConfigInput::SpaceMode::Interpixel) ofs << "Space Mode: Interpixel \n";

    ofs << "Levels: " << bcFlowInput.odrConfigInput.levels << "\n";
    ofs << "Radius: " << bcFlowInput.bcInput.radius << "\n";

    if( bcFlowInput.odrConfigInput.neighborhood==BCFlowInput::ODRConfigInput::NeighborhoodType::FourNeighborhood ) ofs << "Neighborhood: 4\n";
    if( bcFlowInput.odrConfigInput.neighborhood==BCFlowInput::ODRConfigInput::NeighborhoodType::EightNeighborhood ) ofs << "Neighborhood: 8\n";


    ofs << "Squared Curvature Weight: " << bcFlowInput.bcInput.sqTermWeight << " \n";
    ofs << "Length Weight: " << bcFlowInput.bcInput.lengthTermWeight << " \n";
    ofs << "Data Weight: " << bcFlowInput.bcInput.dataTermWeight << " \n";



}
