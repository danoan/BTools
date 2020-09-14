#include "MaskSelector.h"

using namespace SeedSelector;

MaskSelector::MouseEvent::MouseEvent(const cv::Mat& cvImg,
                                     cv::Scalar rectColor,
                                     unsigned char penWidth):
        _cvImg(cvImg),
        _rectColor(rectColor),
        _penWidth(penWidth),
        _flagDrawRect(false)
{
    this->restart();
}

void MaskSelector::MouseEvent::callbackFn(int event,
                                          int x,
                                          int y,
                                          int flags,
                                          void *param)
{
    MouseEvent* me = (MouseEvent*) param;
    me->change(true);
    switch(event)
    {
        case cv::MouseEventTypes::EVENT_LBUTTONDOWN:
        {
            me->_flagDrawRect = true;
            me->_p1 = cv::Point(x,y);
            break;
        }
        case cv::MouseEventTypes::EVENT_MOUSEMOVE:
        {
            if(!me->_flagDrawRect) break;

            me->_p2 = cv::Point(x,y);
            me->_blendImage = me->_cvImg.clone();
            cv::line(me->_tempMask,me->_p1,me->_p2,255,me->_penWidth);


            me->_blendImage.setTo(me->_rectColor,me->_tempMask);

            me->_p1 = me->_p2;
            break;
        }
        case cv::MouseEventTypes::EVENT_LBUTTONUP:
        {
            me->_flagDrawRect = false;
            me->_mask = me->_tempMask;
            break;
        }
    }

}