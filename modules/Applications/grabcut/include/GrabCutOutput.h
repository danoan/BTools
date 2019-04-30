#ifndef BINOCS_GRABCUTOUTPUT_H
#define BINOCS_GRABCUTOUTPUT_H

namespace GrabCut
{
    struct GrabCutOutput
    {
        cv::Mat grabCutMask;
        cv::Mat segMaskResult;
    };
}

#endif //BINOCS_GRABCUTOUTPUT_H
