#include <BinOCS/API.h>
#include "InteractiveControl.h"

using namespace BTools::Application;

InteractiveControl::InteractiveControl(const BCFlowInput& bcFlowInput,
                                       const std::string& imageFilePath,
                                       std::string outputFolder)
{
    boost::filesystem::create_directories(outputFolder);

    typedef BinOCS::API::SegCorrect::BCAOutput BCAOutput;
    BCAOutput bcaOutput = BinOCS::API::segCorrect(imageFilePath,
                                                  bcFlowInput.bcInput,
                                                  bcFlowInput.odrConfigInput,
                                                  bcFlowInput.flowProfile,
                                                  bcFlowInput.maxIterations);

    const BCAOutput::EnergySolution& solution = bcaOutput.energySolution;

    std::string graphCutSegFilepath = outputFolder + "/gc-seg.png";
    std::string correctedSegFilepath = outputFolder +"/corrected-seg.png";
    std::string maskBoundaryFilepath = outputFolder +"/mask-boundary.png";



    const DigitalSet& boundaryMaskDs = bcaOutput.energySolution.outputDS;
    Point dims = boundaryMaskDs.domain().upperBound() - boundaryMaskDs.domain().lowerBound() + Point(1,1);
    cv::Mat maskBoundaryImgGS = cv::Mat::zeros( dims(1),dims(0) ,CV_8UC1);
    DIPaCUS::Representation::digitalSetToCVMat(maskBoundaryImgGS,boundaryMaskDs);

    cv::Mat maskBoundaryImgColor( maskBoundaryImgGS.size(),CV_8UC3);
    cv::cvtColor(maskBoundaryImgGS,maskBoundaryImgColor,cv::COLOR_GRAY2RGB);

    BTools::Utils::setHighlightedBorder(maskBoundaryImgColor,cv::Vec3b(255,255,0));

    cv::imwrite(graphCutSegFilepath,bcaOutput.imgSeg);
    cv::imwrite(correctedSegFilepath,bcaOutput.imgOutput);
    cv::imwrite(maskBoundaryFilepath,maskBoundaryImgColor);

    double outputElasticaEnergy,inputElasticaEnergy;
    SCaBOliC::Utils::ISQEvaluation(outputElasticaEnergy,
                                   solution.outputDS,SCaBOliC::Utils::ISQEvaluation::MDCA);

    DGtal::Z2i::Domain baseImageDomain( Point(0,0),Point(bcaOutput.imgSeg.cols,bcaOutput.imgSeg.rows) );
    DigitalSet baseImageDS( baseImageDomain );

    DIPaCUS::Representation::CVMatToDigitalSet(baseImageDS,bcaOutput.imgSeg);
    SCaBOliC::Utils::ISQEvaluation(inputElasticaEnergy,
                                   baseImageDS,SCaBOliC::Utils::ISQEvaluation::MDCA);

    std::ofstream ofs(outputFolder + "/energy.txt");
    ofs << "GrabCut Segmentation Elastica Energy: " << inputElasticaEnergy << "\n"
        << "Boundary Correction Elastica Energy: " << outputElasticaEnergy << std::endl;
    ofs.close();

    cv::destroyAllWindows();

    cv::Rect r = BTools::Utils::computeBoundingBox(bcaOutput.imgSeg);

    BTools::Utils::showManyImages("Boundary Correction",2,bcaOutput.imgSeg(r),bcaOutput.imgOutput(r));

}


