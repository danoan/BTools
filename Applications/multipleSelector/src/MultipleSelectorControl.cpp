#include "MultipleSelectorControl.h"

using namespace BTools::Application;

const char MultipleSelectorControl::ESCAPE=27;
const char MultipleSelectorControl::ESPACE=32;

MultipleSelectorControl::MultipleSelectorControl(std::string imgFilePath,
                                                 std::string windowName,
                                                 std::string outputFilepath)
{
    SeedInput msi;

    msi.imgFilePath = imgFilePath;
    bool onExecution=true;
    int key;
    while(onExecution)
    {
        key = cv::waitKey(0);
        switch(key)
        {
            case ESPACE:    //NEXT
            {
                onExecution=false;
                break;
            }
            case ESCAPE:    //REMOVE last selection and do it again
            {
                if(msi.vsp.size()>0)
                {
                    msi.vsp.erase(msi.vsp.begin()+msi.vsp.size());
                    msi.vectorOfROI.erase(msi.vectorOfROI.begin()+msi.vectorOfROI.size());
                }

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

                break;
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