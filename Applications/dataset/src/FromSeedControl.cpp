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
    cv::Mat baseImage = cv::imread(imgFilePath,CV_LOAD_IMAGE_COLOR);
    GCApplication::executeFromSeed(result,selectorOutput);

    CVMatDistribution fgDistr(baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(baseImage,
                              result.bgModel);

    ImageDataInput imageDataInput(fgDistr,
                                  bgDistr,
                                  baseImage,
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


    SCaBOliC::Utils::MDCAISQEvaluation(output.MDCAElasticaValue,
                                       solution.outputDS);


    /*    SCaBOliC::Utils::IIISQEvaluation(output.IIElasticaValue,
                                         solution.outputDS); */

    output.IIElasticaValue =-1;
    
    BTools::Utils::setHighlightedBorder(result.foreground,BTools::Utils::ColorType(255,255,0));
    BTools::Utils::setHighlightedBorder(bcaOutput.imgOutput,BTools::Utils::ColorType(255,255,0));

    cv::imwrite(outputFolder + "/gc-seg.bmp",result.foreground);
    cv::imwrite(outputFolder +"/corrected-seg.bmp",bcaOutput.imgOutput);
    
}
