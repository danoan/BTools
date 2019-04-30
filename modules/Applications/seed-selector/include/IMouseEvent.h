#ifndef BINOCS_MOUSEEVENT_H
#define BINOCS_MOUSEEVENT_H

namespace SeedSelector
{
    class IMouseEvent
    {
    public:
        virtual void restart(const cv::Mat&)=0;
        virtual void restart()=0;
        virtual const cv::Mat& blendImage()=0;
        virtual const cv::Mat& mask()=0;

        virtual cv::Scalar& rectColor()=0;
        virtual unsigned char& penWidth()=0;
        virtual void change(bool)=0;
        virtual bool hasChange()=0;

    };
}

#endif //BINOCS_MOUSEEVENT_H
