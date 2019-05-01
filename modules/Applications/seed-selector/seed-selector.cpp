#include <iostream>
#include <opencv2/highgui.hpp>


#include "InputData.h"
#include "GUIControl.h"


using namespace SeedSelector;

int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    GUIData gd = GUIData::initGUIData("SeedSelector",id.outputFolder,id.imagePath,id.once);
    cv::namedWindow(gd.windowName);

    gd.loadPbFgMask(id.unknownImageMask);
    gd.loadFgMask(id.fgImageMask);
    gd.loadBgMask(id.bgImageMask);

    cv::imshow(gd.windowName,gd.cvImg);



    cv::createButton("Probably Foreground",probablyForegroundCallback,&gd,cv::QT_RADIOBOX,true);
    cv::createButton("Foreground",foregroundCallback,&gd,cv::QT_RADIOBOX,false);
    cv::createButton("Background",backgroundCallback,&gd,cv::QT_RADIOBOX,false);
    cv::createButton("Restart",restartCallback,&gd);

    cv::createButton("Save",saveCallback,&gd);


    displayStatusBar(gd);
    setRectMouseCallback(gd);


    bool onExecution=true;
    while(onExecution)
    {
        int key=cv::waitKey(10);
        switch(key)
        {
            case 'p':{ probablyForegroundCallback(1,&gd); break; }
            case 'f':{ foregroundCallback(1,&gd); break; }
            case 'b':{ backgroundCallback(1,&gd); break; }
            case 'r':{ restartCallback(1,&gd); break; }
            case 's':{ saveCallback(1,&gd); break; }
            case '+':
            {
                gd.penWidth += gd.penWidth<255?1:0;
                displayStatusBar(gd);
                break;
            }
            case '-':
            {
                gd.penWidth -= gd.penWidth>0?1:0;
                displayStatusBar(gd);
                break;
            }
        }
        refreshWindow(gd);
    }



    return 0;


}