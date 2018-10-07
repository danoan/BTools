#include "../include/MultipleSelectorControl.h"

using namespace BTools::Application;

MultipleSelectorControl::MultipleSelectorControl(std::string imgFilePath,
                                                 std::string windowName,
                                                 std::string outputFilepath)
{
    SeedInput msi;

    msi.imgFilePath = imgFilePath;
    bool onExecution=true;
    while(onExecution)
    {
        int key = cv::waitKey(0);
        switch(key)
        {
            case 27:
            {
                onExecution = false;
                break;
            }
            default:
            {
                SelectorOutput selectorOutput;
                SeedSelector selector(selectorOutput,
                                      windowName,
                                      imgFilePath);

                std::vector<cv::Point> vp;
                includePointsFromGCMask(vp,selectorOutput.sureFrg);
                msi.vsp.push_back(vp);

                cv::Size imgSize = cv::imread(imgFilePath).size();
                msi.width = imgSize.width;
                msi.height = imgSize.height;

                msi.vectorOfROI.push_back(selectorOutput.possibleFrg);
            }

        }

    }

    DataWriter::write(msi,outputFilepath);
}

void MultipleSelectorControl::includePointsFromGCMask(std::vector<cv::Point> &vp,
                                                      cv::Mat gcMask)
{
    int nRows = gcMask.rows;
    int nCols = gcMask.cols;
    unsigned char* ptr;
    for(int i=0;i<nRows;++i)
    {
        ptr = gcMask.ptr<unsigned char>(i);
        for(int j=0;j<nCols;++j)
        {
            if(ptr[j]==cv::GrabCutClasses::GC_FGD ||
               ptr[j]==cv::GrabCutClasses::GC_PR_FGD)
            {
                vp.push_back(cv::Point(j,i));
            }
        }
    }
}