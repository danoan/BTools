#include "FromSeedControl.h"

using namespace BTools::Application;

FromSeedControl::FromSeedControl(OptOutput& output,
                                 const std::string& imgFilePath, 
                                 const BCFlowInput& bcFlowInput, 
                                 const SelectorOutput& selectorOutput, 
                                 const std::string& outputFolder)
{
    boost::filesystem::create_directories(outputFolder);

    GrabCutResult result;
    cv::Mat baseImage = cv::imread(imgFilePath,cv::IMREAD_COLOR);
    GCApplication::executeFromSeed(result,selectorOutput);

    CVMatDistribution fgDistr(baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(baseImage,
                              result.bgModel);

    ImageDataInput imageDataInput(fgDistr,
                                  bgDistr,baseImage,
                                  result.foreground);


    BCAInput bcaInput(bcFlowInput.bcInput,
                      imageDataInput,
                      bcFlowInput.odrConfigInput,
                      bcFlowInput.flowProfile);


    BinOCS::API::SegCorrect::BCAOutput bcaOutput = BinOCS::API::correct(bcaInput,
                                                                        bcFlowInput.maxIterations);
    const BCSolution& solution = bcaOutput.energySolution;

    
    output.optEnergyValue = solution.energyValue;
    output.unlabeled = solution.unlabeled;
    output.inputImage = result.foreground;
    output.outputImage = bcaOutput.imgOutput;


    SCaBOliC::Utils::ISQEvaluation(output.MDCAElasticaValue,
                                   solution.outputDS,
                                   SCaBOliC::Utils::ISQEvaluation::MDCA);


    /*    SCaBOliC::Utils::IIISQEvaluation(output.IIElasticaValue,
                                         solution.outputDS); */

    output.IIElasticaValue =-1;

    BTools::Utils::setHighlightedBorder(result.foreground,BTools::Utils::ColorType(255,255,0));
    BTools::Utils::setHighlightedBorder(bcaOutput.imgOutput,BTools::Utils::ColorType(255,255,0));


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

    cv::imwrite(graphCutSegFilepath,result.foreground);
    cv::imwrite(correctedSegFilepath,bcaOutput.imgOutput);
    cv::imwrite(maskBoundaryFilepath,maskBoundaryImgColor);
}
