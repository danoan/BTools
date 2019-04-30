#include "RectSelector.h"

using namespace SeedSelector;

RectSelector::MouseEvent::MouseEvent(const cv::Mat& cvImg,
                                     cv::Scalar rectColor,
                                     unsigned char penWidth):_cvImg(cvImg),
                                                             _rectColor(rectColor),
                                                             _penWidth(penWidth)
{
    this->restart();
}

void RectSelector::MouseEvent::callbackFn(int event,
                                          int x,
                                          int y,
                                          int flags,
                                          void *param)

{
    MouseEvent* me = (MouseEvent*) param;
    me->change(true);
    switch(event)
    {
        case CV_EVENT_LBUTTONDOWN:
        {
            me->_p1 = cvPoint(x,y);
            me->_flagDrawRect = true;
            break;
        }
        case CV_EVENT_MOUSEMOVE:
        {
            if(!me->_flagDrawRect) break;
            me->_blendImage = me->_cvImg.clone();

            if(x>=me->_blendImage.size().width) x = me->_blendImage.size().width-1;
            if(y>=me->_blendImage.size().height) y = me->_blendImage.size().height-1;

            if(x<0) x = 0;
            if(y<0) y = 0;

            me->_p2 = cvPoint(x,y);
            cv::rectangle( me->_blendImage,me->_p1,me->_p2, 255,4);
            cv::rectangle( me->_mask,me->_p1,me->_p2, 255,cv::FILLED);

            break;
        }
        case CV_EVENT_LBUTTONUP:
        {
            me->_flagDrawRect = false;
            break;
        }
    }

}