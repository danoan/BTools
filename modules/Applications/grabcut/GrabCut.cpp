#include <iostream>

#include <opencv2/highgui.hpp>
#include <boost/filesystem.hpp>

#include "InputData.h"
#include "GrabCutOutput.h"
#include "GrabCutApplication.h"


using namespace GrabCut;

GrabCutOutput runGrabCut(const std::string& imgPath,
                         const std::string& unknownMask,
                         const std::string& fgSeedMask,
                         const std::string& bgSeedMask)
{
    cv::Mat cvImg = cv::imread(imgPath);
    GrabCutApplication gca(cvImg);

    gca.setUnknownMask(unknownMask);
    gca.setFGMask(fgSeedMask);
    gca.setBGMask(bgSeedMask);

    return gca.run();
}

void saveOutput(const GrabCutOutput& gco,const cv::Mat& inputImage, const std::string& outputPath)
{
    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());
    cv::FileStorage gcOutputFile(outputPath,cv::FileStorage::WRITE);
    gcOutputFile << "grabCutMask" << gco.grabCutMask;
    gcOutputFile << "segMask" << gco.segMaskResult;
    gcOutputFile << "inputImage" << inputImage;
    gcOutputFile.release();
}

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    cv::Mat inputImg = cv::imread(id.imgPath);
    GrabCutOutput gco = runGrabCut(id.imgPath,id.unknownMask,id.fgSeedMask,id.bgSeedMask);
    saveOutput(gco,inputImg,id.outputObject);


    cv::Mat segResultImg = cv::Mat::zeros(inputImg.size(),CV_8UC4);

    inputImg.copyTo(segResultImg,gco.segMaskResult);

    if(id.outputSegImage!="")
    {
        cv::imwrite(id.outputSegImage,segResultImg);
    }
    if(id.showSeg)
    {
        cv::namedWindow("GrabCut");
        cv::imshow("GrabCut",
                   segResultImg);
    }



    cv::waitKey(0);
}