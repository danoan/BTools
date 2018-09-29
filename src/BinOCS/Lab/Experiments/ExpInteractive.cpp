#include "BinOCS/Lab/Experiments/ExpInteractive.h"

using namespace BinOCS::Lab::Experiments;

ExpInteractive::ExpInteractive(const Model::GrabCorrectionInput& expInput,
                               std::string outputFolder)
{
    boost::filesystem::create_directories(outputFolder);


    GrabCutResult result;
    GCApplication ga(expInput.imagePath,result);

    cv::destroyWindow(ga.windowName);

    CVMatDistribution fgDistr(result.baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(result.baseImage,
                              result.bgModel);


    BCConfigData configData(expInput.bcInput.estimatingBallRadius,
                            fgDistr,
                            bgDistr,
                            expInput.bcInput.dataTermWeight,
                            expInput.bcInput.sqTermWeight,
                            expInput.bcInput.lengthTermWeight);


    BCSolution solution = BCApplication::solutionModel(result.foreground);
    BCApplication bca(solution,
                      expInput.bcInput.maxIterations,
                      result.foreground,
                      configData);

    DisplayData dd = bca.displayResult(solution,
                                       result.baseImage,
                                       result.foreground);

    cv::Mat enhancedImg = dd.imgOutput.clone();

    Utils::enhance(enhancedImg,
                   result.baseImage,
                   dd.removedPoints,
                   0.75);

    Utils::enhance(enhancedImg,
                   result.baseImage,
                   dd.includedPoints,
                   1.25);

    DGtal::Board2D board;
    board << dd.includedPoints;
    board.saveEPS( (outputFolder +"/included.eps").c_str());

    board.clear();
    board << dd.removedPoints;
    board.saveEPS((outputFolder + "/removed.eps").c_str());


    cv::imwrite(outputFolder + "/gc-seg.jpg",result.foreground);
    cv::imwrite(outputFolder +"/corrected-seg.jpg",dd.imgOutput);


    /*
    BinOCS::Experiments::Utils::showManyImages("Segmentation Result",
                                               3,
                                               result.foreground(extendedROI),
                                               dd.imgOutput(extendedROI),
                                               enhancedImg(extendedROI));
    */

    cv::destroyAllWindows();

}


