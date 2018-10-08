#ifndef BTOOLS_MODEL_SEEDSEQUENCEINPUT_H
#define BTOOLS_MODEL_SEEDSEQUENCEINPUT_H

#include <fstream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <BinOCS/RegionSelector/SeedSelectorApplication.h>

namespace BTools
{
    namespace Model
    {
        class SeedSequenceInput
        {
        public:
            typedef std::vector< std::vector<cv::Point> > VectorOfSequenceOfPoints;
            typedef std::vector<cv::Rect> VectorOfRect;

            typedef BinOCS::RegionSelector::SeedSelectorApplication::SelectorOutput SelectorOutput;

        public:
            inline unsigned int numSeed(){return vsp.size();}

            void getSelector(SelectorOutput &selectorOutput,
                             unsigned int index)
            {
                cv::Mat& mask = selectorOutput.sureFrg;

                mask = cv::Mat::zeros(height,width,CV_8UC1);
                const std::vector<cv::Point>& curr = vsp[index];
                for(auto it=curr.begin();it!=curr.end();++it)
                {
                    mask.at<unsigned char>(*it) = 1;
                }

                selectorOutput.possibleFrg = vectorOfROI[index];
            }

        public:
            std::string imgFilePath;
            int width,height;

            VectorOfSequenceOfPoints vsp;
            VectorOfRect vectorOfROI;
        };
    }
}

#endif //BTOOLS_MODEL_SEEDSEQUENCEINPUT_H
