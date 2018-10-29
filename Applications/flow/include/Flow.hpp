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

    DigitalSet ds(gd.getDomain());
    Shapes::digitalShaper(ds,gd);


    std::string currImagePath = flowFolder + "/00.pgm";
    exportImageFromDigitalSet(ds,currImagePath);

    os << "Image: " << imageName << "\n"
       << std::endl;

    cv::Mat img = cv::imread(currImagePath,CV_LOAD_IMAGE_COLOR);
    
    
    MockDistribution frDistr;
    MockDistribution bkDistr;




    std::vector<TableEntry> entries;

    BCAOutput::EnergySolution firstSolution(ds.domain());
    firstSolution.outputDS = ds;
    firstSolution.energyValue = -1;
    entries.push_back(TableEntry(firstSolution,"IT 0"));

    
    Domain solutionDomain(Point(0,0),Point(img.cols-1,img.rows-1));
    int i=1;
    do
    {
        img = cv::imread(currImagePath,CV_LOAD_IMAGE_COLOR);
        
        BCAInput bcaInput(bcFlowInput.bcInput,
                          bcFlowInput.flowConfigInput,
                          frDistr,
                          bkDistr,
                          img,
                          img);
        
        BCAOutput bcaOutput(bcaInput);
        
        BinOCS::BoundaryCorrection::BCApplication BCA(bcaOutput,
                                                      bcaInput,
                                                      1);

        entries.push_back(TableEntry(bcaOutput.energySolution,"IT " + std::to_string(i)));

        currImagePath = flowFolder + "/" + BTools::Utils::nDigitsString(i,2) + ".pgm";


        exportImageFromDigitalSet(bcaOutput.energySolution.outputDS,currImagePath);

        ++i;
    }while(i<bcFlowInput.maxIterations);



    printTable(entries,os);

}
