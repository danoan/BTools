#ifndef BINOCS_EXPERIMENTS_EXPDATAINPUT_H
#define BINOCS_EXPERIMENTS_EXPDATAINPUT_H

#include <fstream>
#include <opencv2/core/types.hpp>

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            struct ROISequenceInput
            {
                std::string imgFilePath;
                std::vector<cv::Rect> vectorOfROI;

                static ROISequenceInput read(std::string filepath);
                static void write(const ROISequenceInput& dataToWrite,
                                  std::string outputFilepath);
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_EXPDATAINPUT_H
