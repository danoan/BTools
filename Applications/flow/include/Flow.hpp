#include "Flow.h"

using namespace BTools::Application::Illustration;
using namespace BTools::Application;


template<class TShape>
void Flow::shapeFlow(TShape shape,
                     const BCFlowInput& bcFlowInput,
                     double h,
                     std::string imageName,
                     std::string outputFolder,
                     bool exportRegions)
{
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

    os << "Image: " << imageName << "\n"
       << std::endl;

    cv::Mat img = cv::imread(currImagePath,CV_LOAD_IMAGE_COLOR);
    
    
    MockDistribution frDistr;
    MockDistribution bkDistr;


    std::function<Point(int)> MCFN;

    MCFN = [](int nit){ return Point(0,0); };


    std::vector<TableEntry> entries;

    BCAOutput::EnergySolution firstSolution(ds.domain());
    firstSolution.outputDS = ds;
    firstSolution.energyValue = -1;
    entries.push_back(TableEntry(firstSolution,"IT 0"));

    std::vector<IBCControlVisitor*> visitors;
    visitors.push_back(new ContributionSurface() );
    
    Domain solutionDomain(Point(0,0),Point(img.cols-1,img.rows-1));
    int i=1;
    do
    {
        cv::Mat imgTT = cv::imread(currImagePath,CV_LOAD_IMAGE_COLOR);
        
        BCAInput bcaInput(bcFlowInput.bcInput,
                          bcFlowInput.flowConfigInput,
                          frDistr,
                          bkDistr,
                          imgTT,
                          imgTT);

        BCAOutput bcaOutput(bcaInput);
        
        BinOCS::BoundaryCorrection::BCApplication BCA(bcaOutput,
                                                      bcaInput,
                                                      1,
                                                      visitors.begin(),
                                                      visitors.end());

        entries.push_back(TableEntry(bcaOutput.energySolution,"IT " + std::to_string(i)));

        currImagePath = flowFolder + "/" + BTools::Utils::nDigitsString(i,4) + ".pgm";


        const BCAOutput::EnergySolution& solution = bcaOutput.energySolution;
        DigitalSet translatedBackDS( Domain( Point(0,0),
                                             Point(imgTT.cols-1,imgTT.rows-1)
        ) );

        for (auto it = solution.outputDS.begin(); it != solution.outputDS.end(); ++it)
        {
            translatedBackDS.insert(*it + bcaInput.translation + MCFN(i-1) );
        }
            


        exportImageFromDigitalSet(translatedBackDS,flowDomain,currImagePath);

        ++i;
    }while(i<bcFlowInput.maxIterations);


    delete visitors[0];

    printTable(entries,os);

}
