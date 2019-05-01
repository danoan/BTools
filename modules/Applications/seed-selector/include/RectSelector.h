#ifndef BTools_RECTSELECTOR_H
#define BTools_RECTSELECTOR_H

#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "IMouseEvent.h"

namespace SeedSelector
{
    namespace RectSelector
    {
        class MouseEvent:public IMouseEvent
        {
        public:
            MouseEvent(const cv::Mat& cvImg,
                       cv::Scalar rectColor=cv::Scalar(255,0,0),
                       unsigned char penWidth=3);

            static void callbackFn(int event,
                                   int x,
                                   int y,
                                   int flags,
                                   void *param);

            void restart(const cv::Mat& mask)
            {
                std::vector<std::vector<cv::Point> > contours;
                cv::findContours( mask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

                cv::Rect r = cv::boundingRect(contours[0]);

                this->_p1 = r.tl();
                this->_p2 = r.br();

                cv::rectangle(this->_blendImage,this->_p1,this->_p2,this->_rectColor,4);
                cv::rectangle(this->_mask,this->_p1,this->_p2, 255,cv::FILLED);

                this->_flagDrawRect=false;
                this->_change=true;
            }

            void restart()
            {
                _mask = cv::Mat::zeros(_cvImg.size(),CV_8UC1);
                _flagDrawRect = false;
                _blendImage = _cvImg.clone();
                _change=true;
            }

            const cv::Mat& blendImage(){ return _blendImage; }
            const cv::Mat& mask(){ return _mask; }
            cv::Scalar& rectColor(){ return _rectColor; }
            unsigned char& penWidth(){ return _penWidth; }
            void change(bool change){_change=change;}
            bool hasChange(){return _change;}

        private:

            const cv::Mat& _cvImg;
            cv::Mat _blendImage;
            cv::Mat _mask;
            bool _change;

            unsigned char _penWidth;
            cv::Point _p1,_p2;
            cv::Scalar _rectColor;
            bool _flagDrawRect;


        };
    }
}

#endif //BTools_RECTSELECTOR_H
