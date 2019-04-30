#ifndef BINOCS_SEEDPICKER_MASKSELECTOR_H
#define BINOCS_SEEDPICKER_MASKSELECTOR_H

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "IMouseEvent.h"

namespace SeedSelector
{
    namespace MaskSelector
    {
        class MouseEvent: public SeedSelector::IMouseEvent
        {

        public:
            MouseEvent(const cv::Mat& cvImg,
                       cv::Scalar rectColor=cv::Scalar(0,255,0),
                       unsigned char penWidth=1);

            void restart(const cv::Mat& mask)
            {
                this->_tempMask = mask;
                this->_mask= mask;
                this->_flagDrawRect=false;
                this->_change=true;
            }

            void restart()
            {
                this->_tempMask = cv::Mat::zeros(_cvImg.size(),CV_8UC1);
                this->_mask= cv::Mat::zeros(_cvImg.size(),CV_8UC1);
                this->_flagDrawRect=false;
                this->_change=true;
            }

            static void callbackFn(int event,
                                   int x,
                                   int y,
                                   int flags,
                                   void* param);

            const cv::Mat& blendImage(){ std::cout << _rectColor << std::endl; return this->_blendImage; }
            const cv::Mat& mask(){ return this->_mask; }
            cv::Scalar& rectColor(){ return this->_rectColor; }
            unsigned char& penWidth(){ return this->_penWidth; }
            void change(bool change){_change=change;}
            bool hasChange(){return _change;}

        private:
            const cv::Mat& _cvImg;

            cv::Mat _blendImage;
            cv::Mat _mask;
            cv::Scalar _rectColor;
            unsigned char _penWidth;
            bool _change;

            cv::Mat _tempMask;
            cv::Point _p1,_p2;
            bool _flagDrawRect;

        };

    }
}

#endif //BINOCS_SEEDPICKER_MASKSELECTOR_H
