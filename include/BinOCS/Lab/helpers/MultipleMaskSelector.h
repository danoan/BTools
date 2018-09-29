#ifndef BINOCS_EXPERIMENTS_MULTIPLEMASKSELECTOR_H
#define BINOCS_EXPERIMENTS_MULTIPLEMASKSELECTOR_H

#include <string>
#include "BinOCS/Application/RegionSelector/SeedSelectorApplication.h"
#include "BinOCS/Lab/model/input/SeedSequenceInput.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Helpers
        {
            class MultipleMaskSelector
            {
            public:
                typedef BinOCS::Application::SeedSelectorApplication SeedSelector;
                typedef SeedSelector::SelectorOutput SelectorOutput;
                typedef BinOCS::Lab::Model::SeedSequenceInput MaskSequenceInput;

            public:
                MultipleMaskSelector(std::string imgFilePath,
                                     std::string windowName,
                                     std::string outputFilepath)
                {
                    MaskSequenceInput msi;

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

                    MaskSequenceInput::write(msi,outputFilepath);
                }

            private:
                void includePointsFromGCMask(std::vector<cv::Point>& vp,
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

            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_MULTIPLEMASKSELECTOR_H
