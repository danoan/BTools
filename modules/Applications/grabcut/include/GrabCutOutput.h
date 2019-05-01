#ifndef BTools_GRABCUTOUTPUT_H
#define BTools_GRABCUTOUTPUT_H

namespace GrabCut
{
    struct GrabCutOutput
    {
        cv::Mat grabCutMask;
        cv::Mat segMaskResult;
    };
}

#endif //BTools_GRABCUTOUTPUT_H
