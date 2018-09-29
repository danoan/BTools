#include "BinOCS/Lab/Experiments/ExpFromSeed.h"

using namespace BinOCS::Lab::Experiments;


ExpFromSeed::ExpFromSeed(const std::string& imgFilePath,
                         const Model::BCorrectionInput& bcInput,
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

    BCConfigData configData(bcInput.estimatingBallRadius,
                            fgDistr,
                            bgDistr,
                            bcInput.dataTermWeight,
                            bcInput.sqTermWeight,
                            bcInput.lengthTermWeight);


    BCSolution solution = BCApplication::solutionModel(result.foreground);
    BCApplication bca(solution,
                      bcInput.maxIterations,
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


//    BinOCS::Experiments::Utils::showManyImages("Segmentation Result",
//                                               3,
//                                               result.foreground(extendedROI),
//                                               dd.imgOutput(extendedROI),
//                                               enhancedImg(extendedROI));
//
//
//    cv::destroyAllWindows();
}