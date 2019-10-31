#ifndef BTOOLS_SUMMARY_FLOW_INPUTDATA_H
#define BTOOLS_SUMMARY_FLOW_INPUTDATA_H

#include <vector>

#include "types.h"

namespace SummaryFlow
{
    struct InputData
    {
        InputData()
        {
            jumpStep=5;
            pixelMaskPath="";
            dirsMaskPath="";
            flowImagesFolderPath="";
            outputFilePath="";
            iot=ImageOutputType::SVG;
        }

        int jumpStep;
        std::string pixelMaskPath;
        std::string dirsMaskPath;

        ImageOutputType iot;
        std::string flowImagesFolderPath;
        std::string outputFilePath;
    };
}

#endif //BTOOLS_SUMMARY_FLOW_INPUTDATA_H
