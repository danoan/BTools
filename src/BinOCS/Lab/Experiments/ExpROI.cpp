#include "BinOCS/Lab/Experiments/ExpROI.h"

using namespace BinOCS::Lab::Experiments;


ExpROI::ExpROI(const Model::ROICorrectionInput& input,
               const std::string& outputFolder)
{
    boost::filesystem::create_directories(outputFolder);

    GCApplication::GrabCutResult result;
    cv::Mat baseImage = cv::imread(input.roiInput.imgFilePath,CV_LOAD_IMAGE_COLOR);
    GCApplication::executeFromROI(result,baseImage,input.roiInput.vectorOfROI[0]);

    CVMatDistribution fgDistr(baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(baseImage,
                              result.bgModel);

    BCConfigData configData(input.bcInput.estimatingBallRadius,
                            fgDistr,
                            bgDistr,
                            input.bcInput.dataTermWeight,
                            input.bcInput.sqTermWeight,
                            input.bcInput.lengthTermWeight);


    BCSolution solution = BCApplication::solutionModel(result.foreground);
    BCApplication bca(solution,
                      input.bcInput.maxIterations,
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


    cv::Rect extendedROI = result.ROI;
    extendedROI.x-=5;
    extendedROI.y-=5;
    extendedROI.width+=5;
    extendedROI.height+=5;

    cv::imwrite(outputFolder + "/gc-seg.jpg",result.foreground(extendedROI));
    cv::imwrite(outputFolder +"/corrected-seg.jpg",dd.imgOutput(extendedROI));


//    BinOCS::Experiments::Utils::showManyImages("Segmentation Result",
//                                               3,
//                                               result.foreground(extendedROI),
//                                               dd.imgOutput(extendedROI),
//                                               enhancedImg(extendedROI));
//
//
//    cv::destroyAllWindows();
}