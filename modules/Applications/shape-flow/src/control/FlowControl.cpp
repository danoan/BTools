#include "control/FlowControl.h"

using namespace ShapeFlow;

FlowControl::DigitalSet FlowControl::resolveShape(Shape shape,double gridStep)
{
    int radius=20;
    if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
    else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
    else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
    else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
    else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
    else if(shape.type==ShapeType::Wave) return DIPaCUS::Shapes::wave(gridStep,1200,radius*3,radius*6,0.01);
    else
    {
        cv::Mat img = cv::imread(shape.imagePath,CV_8UC1);
        Domain domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(img.cols-1,img.rows-1) );
        DigitalSet ds(domain);
        DIPaCUS::Representation::CVMatToDigitalSet(ds,img,1);
        return ds;
    }
}

FlowControl::FlowControl(const BCFlowInput& bcFlowInput,
                         Shape shape,
                         double gridStep,
                         const std::string& outputFolder,
                         std::ostream& osLog)
{
    boost::filesystem::create_directories(outputFolder);
    std::ofstream ofs(outputFolder + "/input-data.txt");

    DataWriter::printFlowMetadata(bcFlowInput,ofs);
    ofs.flush();
    ofs.close();

    DigitalSet ds = resolveShape(shape,gridStep);
    shapeFlow( ds,bcFlowInput,outputFolder,osLog );
}

std::vector<DataWriter::TableEntry> FlowControl::initEntries(const DigitalSet& ds)
{
    std::vector<DataWriter::TableEntry> entries;

    BCAOutput::EnergySolution firstSolution(ds.domain());
    firstSolution.outputDS = ds;
    firstSolution.energyValue = -1;
    entries.push_back(DataWriter::TableEntry(firstSolution,"0"));

    return entries;
}

FlowControl::BCAOutput FlowControl::boundaryCorrection(const BCFlowInput& bcFlowInput,
                                                       const cv::Mat& currentImage,
                                                       Point& translation)
{
    MockDistribution frDistr;
    MockDistribution bkDistr;

    ImageDataInput imageDataInput(frDistr,
                                  bkDistr,
                                  currentImage,
                                  currentImage);

    BCAInput bcaInput(bcFlowInput.bcInput,
                      imageDataInput,
                      bcFlowInput.odrConfigInput,
                      bcFlowInput.flowProfile);

    BCAOutput bcaOutput(bcaInput);

    BTools::Core::BCApplication BCA(bcaOutput,
                                    bcaInput,
                                    1,
                                    false);

    translation = imageDataInput.translation;

    return bcaOutput;
}

FlowControl::DigitalSet FlowControl::correctTranslation(const BCAOutput::EnergySolution& solution,
                                                        const cv::Mat& currentImage,
                                                        const Point& translation)
{
    DigitalSet translatedBackDS( Domain( Point(0,0),
                                         Point(currentImage.cols-1,currentImage.rows-1)
    ) );

    for (auto it = solution.outputDS.begin(); it != solution.outputDS.end(); ++it)
    {
        translatedBackDS.insert(*it + translation );
    }

    return translatedBackDS;
}

void FlowControl::checkBounds(const DigitalSet& ds, const Domain& domain)
{
    Point lb,ub;
    ds.computeBoundingBox(lb,ub);

    if(lb(0) <= domain.lowerBound()(0)+1 ||
       lb(1) <= domain.lowerBound()(1)+1 ||
       ub(0) >= domain.upperBound()(0)-1 ||
       ub(1) >= domain.upperBound()(1)-1 )
    {
        throw std::runtime_error("Result image is too big.");
    }

    if(ds.size()<10) throw std::runtime_error("Result image is too small.");
}

void FlowControl::shapeFlow(const DigitalSet& _ds,
                            const BCFlowInput& bcFlowInput,
                            const std::string& outputFolder,
                            std::ostream& osLog)
{
    BTools::Utils::Timer::start();
    
    osLog << "Flow Start: " << bcFlowInput.inputName << "\n";
    osLog << "Iterations (" << bcFlowInput.maxIterations << "): ";


    boost::filesystem::create_directories(outputFolder);
    std::string currImagePath = outputFolder + "/" + BTools::Utils::nDigitsString(0,4) + ".pgm";
    std::ofstream os(outputFolder + "/" + bcFlowInput.inputName + ".txt");


    DigitalSet ds = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(_ds,Point(20,20));
    Domain flowDomain = ds.domain();


    BTools::Utils::exportImageFromDigitalSet(ds,flowDomain,currImagePath);
    std::vector<TableEntry> entries = initEntries(ds);

    cv::Mat img = cv::imread(currImagePath,cv::IMREAD_COLOR);
    Domain solutionDomain(Point(0,0),Point(img.cols-1,img.rows-1));

    int i=1;
    try
    {
        do
        {
            osLog << "|";

            std::vector<IBCControlVisitor*> visitors;
            cv::Mat currentImage = cv::imread(currImagePath,cv::IMREAD_COLOR);


                Point translation;
                BCAOutput bcaOutput = boundaryCorrection(bcFlowInput,currentImage,translation);

                entries.push_back(TableEntry(bcaOutput.energySolution,std::to_string(i)));

                DigitalSet correctedSet = correctTranslation(bcaOutput.energySolution,currentImage,translation);
                checkBounds(correctedSet,flowDomain);


                currImagePath = outputFolder + "/" + BTools::Utils::nDigitsString(i,4) + ".pgm";
                BTools::Utils::exportImageFromDigitalSet(correctedSet,flowDomain,currImagePath);


            ++i;
        }while(i<bcFlowInput.maxIterations);
    }catch(std::exception ex)
    {
        osLog << ex.what() << "\n";
    }

    osLog << "\nWriting Results...";
    DataWriter::printTable(bcFlowInput.inputName,entries,os);
    os << "\n\n";
    BTools::Utils::Timer::end(os);
    osLog << "\n\n";

}


