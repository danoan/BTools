#ifndef BINOCS_EXPERIMENTS_EXPDATAINPUT_H
#define BINOCS_EXPERIMENTS_EXPDATAINPUT_H

#include <opencv2/core/types.hpp>

namespace BinOCS
{
    namespace Experiments
    {
        struct ExpDataInput
        {
            std::string imgFilePath;
            std::vector<cv::Rect> vectorOfROI;

            static ExpDataInput read(std::string filepath);
            static void write(const ExpDataInput& dataToWrite,
                              std::string outputFilepath);
        };
    }
}

#endif //BINOCS_EXPERIMENTS_EXPDATAINPUT_H
