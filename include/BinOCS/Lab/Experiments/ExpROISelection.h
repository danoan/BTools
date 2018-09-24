#ifndef BINOCS_EXPERIMENTS_ROISELECTION_H
#define BINOCS_EXPERIMENTS_ROISELECTION_H

#include <opencv/highgui.h>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include <iostream>
#include <boost/filesystem/operations.hpp>

#include "BinOCS/Lab/model/input/ROISequenceInput.h"

namespace BinOCS
{
    namespace Lab
    {
        namespace Experiments
        {
            class ExpROISelection
            {
            private:
                static const cv::Scalar RECT_COLOR;

                static const int KEY_ENTER;
                static const int KEY_ESCAPE;

                struct MouseEvent
                {
                    MouseEvent(const cv::Mat& baseImg,
                               std::string windowName);

                    cv::Rect rect();

                    const cv::Mat& baseImg;
                    std::string windowName;
                    cv::Point p1,p2;
                    bool flagDrawRect;
                };

                static void mouseEvent(int event,
                                       int x,
                                       int y,
                                       int flags,
                                       void* param);


            public:
                typedef Model::ROISequenceInput Input;

            public:
                ExpROISelection(const std::string& imgFilepath,
                             const std::string& outputFolder,
                                const std::string& filename="data");

            private:
                void executionLoop(Input& dataInput);

            private:
                std::string windowName;
                cv::Mat baseImage;

                MouseEvent me;
            };
        }
    }
}
#endif //BINOCS_EXPERIMENTS_ROISELECTION_H
