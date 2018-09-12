#include "BinOCS/Experiments/ExpInteractive.h"

using namespace BinOCS::Experiments;

ExpInput ExpInteractive::expInput;

ExpInteractive::ExpInteractive(std::string imgFilepath,
                               std::string outputFolder)
{
    boost::filesystem::create_directories(outputFolder);


    GCApplication::GrabCutResult result;
    GCApplication ga(imgFilepath,result);

    cv::destroyWindow(ga.windowName);

    CVMatDistribution fgDistr(result.baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(result.baseImage,
                              result.bgModel);


    BCConfigData configData(expInput.estimatingBallRadius,
                            fgDistr,
                            bgDistr,
                            expInput.dataTermWeight,
                            expInput.sqTermWeight);


    BCSolution solution = BCApplication::solutionModel(result.foreground);
    BCApplication bca(solution,
                      expInput.maxIterations,
                      result.foreground,
                      configData);

    DisplayData dd = bca.displayResult(solution,
                                       result.baseImage,
                                       result.foreground);

    cv::Mat enhancedImg = dd.imgOutput.clone();

    enhance(enhancedImg,
            result.baseImage,
            dd.removedPoints,
            0.75);

    enhance(enhancedImg,
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


    BinOCS::Experiments::Utils::showManyImages("Segmentation Result",
                                               3,
                                               result.foreground(extendedROI),
                                               dd.imgOutput(extendedROI),
                                               enhancedImg(extendedROI));


    cv::destroyAllWindows();

}



void ExpInteractive::enhance(cv::Mat& imgOutput,
                             const cv::Mat& baseImg,
                             const DigitalSet& enhanceDSMask,
                             double factor)
{
    for(auto it=enhanceDSMask.begin();it!=enhanceDSMask.end();++it)
    {
        int row = imgOutput.rows-(*it)(1)-1;
        int col = (*it)(0);

        std::cout << baseImg.at<cv::Vec3b>(row,col) << std::endl;
        std::cout << (baseImg.at<cv::Vec3b>(row,col)*factor) << std::endl;

        imgOutput.at<cv::Vec3b>(row,col) = (baseImg.at<cv::Vec3b>(row,col)*factor);

    }
}

