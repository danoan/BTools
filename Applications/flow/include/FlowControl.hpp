#include "FlowControl.h"

using namespace BTools::Application::Flow;


template<class TShape>
void FlowControl::shapeFlow(TShape shape,
                            const BCFlowInput& bcFlowInput,
                            double h,
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


    typedef DGtal::GaussDigitizer<Space,TShape> MyGaussDigitizer;
    MyGaussDigitizer gd;

    gd.attach(shape);
    gd.init(shape.getLowerBound() + DGtal::Z2i::RealPoint(0,0),
            shape.getUpperBound() + DGtal::Z2i::RealPoint(0,0),h);

    DigitalSet _ds(gd.getDomain());
    Shapes::digitalShaper(_ds,gd);

    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));
    Domain flowDomain = ds.domain();

    std::string currImagePath = flowFolder + "/" + BTools::Utils::nDigitsString(0,4) + ".pgm";
    exportImageFromDigitalSet(ds,flowDomain,currImagePath);

    os << "#Image: " << imageName << "\n#\n";

    cv::Mat img = cv::imread(currImagePath,CV_LOAD_IMAGE_COLOR);
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

        cv::Mat imgTT = cv::imread(currImagePath,CV_LOAD_IMAGE_COLOR);

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
            
            if(translatedBackDS.size()<4) throw std::runtime_error("Result image is too small.");
                
            
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
