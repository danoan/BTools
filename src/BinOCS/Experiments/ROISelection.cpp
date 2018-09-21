#include "BinOCS/Experiments/ROISelection.h"

using namespace BinOCS::Experiments;

const cv::Scalar ROISelection::RECT_COLOR(0,255,0);

const int ROISelection::KEY_ENTER = 13;
const int ROISelection::KEY_ESCAPE = 27;

ROISelection::MouseEvent::MouseEvent(const cv::Mat& baseImg,
                                     std::string windowName):
        baseImg(baseImg),
        windowName(windowName),
        flagDrawRect(false) {}

cv::Rect ROISelection::MouseEvent::rect()
{
    int w = p2.x-p1.x;
    int h = p2.y-p1.y;

    return
            cv::Rect (p1.x,
                      p1.y,
                      w,
                      h);
}

void ROISelection::mouseEvent(int event,
                              int x,
                              int y,
                              int flags,
                              void* param)
{
    MouseEvent* me = (MouseEvent*) param;
    switch(event)
    {
        case CV_EVENT_LBUTTONDOWN:
        {
            me->p1 = cvPoint(x,y);
            me->flagDrawRect = true;
            break;
        }
        case CV_EVENT_MOUSEMOVE:
        {
            if(!me->flagDrawRect) break;

            cv::Mat blendImg = me->baseImg.clone();
            me->p2 = cvPoint(x,y);

            cv::rectangle( blendImg,me->p1,me->p2, cv::Scalar(0,255,0));
            cv::imshow(me->windowName,blendImg);
            break;
        }
        case CV_EVENT_LBUTTONUP:
        {
            me->flagDrawRect = false;
            break;
        }
    }

}


ROISelection::ROISelection(std::string imgFilepath,
                           std::string outputFolder):windowName("ROI-Selection"),
                                                     me(baseImage,windowName)
{
    boost::filesystem::create_directories(outputFolder);

    cv::namedWindow(windowName,CV_WINDOW_AUTOSIZE);
    baseImage = cv::imread(imgFilepath,1);
    cv::setMouseCallback(windowName,mouseEvent,&me);

    cv::imshow(windowName,baseImage);

    ExpDataInput dataInput;
    dataInput.imgFilePath = imgFilepath;
    executionLoop(dataInput);

    ExpDataInput::write(dataInput,outputFolder + "/data.txt");
}

void ROISelection::executionLoop(ExpDataInput& dataInput)
{
    bool onExecution = true;
    int key;
    while(onExecution)
    {
        key = cv::waitKey(0);
        switch(key)
        {
            case KEY_ENTER:
            {
                dataInput.vectorOfROI.push_back(me.rect());
                cv::imshow(windowName,me.baseImg);
                std::cout << "Rect Saved" << std::endl;
                break;
            }
            case 'q':
            {
                onExecution=false;
                break;
            }
        }
    }
    cv::destroyWindow(windowName);
}