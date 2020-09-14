#include "GUIControl.h"

namespace SeedSelector
{
    void displayStatusBar(const GUIData& gd)
    {
        std::string penWidthText = "Pen Width: " + std::to_string( (unsigned int) gd.penWidth );
        cv::displayStatusBar(gd.windowName,penWidthText,1500 );
    }

    void setRectMouseCallback(GUIData& gd)
    {
        cv::setMouseCallback(gd.windowName,NULL);
        cv::setMouseCallback(gd.windowName,SeedSelector::RectSelector::MouseEvent::callbackFn,gd.me());
    }

    void setMaskMouseCallback(GUIData& gd)
    {
        cv::setMouseCallback(gd.windowName,NULL);
        cv::setMouseCallback(gd.windowName,SeedSelector::MaskSelector::MouseEvent::callbackFn,gd.me());
    }

    void refreshWindow(GUIData& gd)
    {
        bool hasChanged=false;

        IMouseEvent* beforeRefresh = gd.me();

        gd.set(GUIData::ProbablyForeground);
        cv::Mat blendImg = gd.me()->blendImage().clone();
        hasChanged = hasChanged || gd.me()->hasChange(); gd.me()->change(false);

        gd.set(GUIData::Foreground);
        blendImg.setTo(gd.me()->rectColor(),gd.me()->mask());
        hasChanged = hasChanged || gd.me()->hasChange(); gd.me()->change(false);

        gd.set(GUIData::Background);
        blendImg.setTo(gd.me()->rectColor(),gd.me()->mask());
        hasChanged = hasChanged || gd.me()->hasChange(); gd.me()->change(false);

        gd.set(beforeRefresh);

        if(hasChanged)
            cv::imshow(gd.windowName, blendImg);
    }

    void probablyForegroundCallback(int state, void* userdata)
    {
        GUIData* gd = (GUIData*) userdata;
        gd->set(GUIData::ProbablyForeground);
        setRectMouseCallback(*gd);
        cv::displayOverlay(gd->windowName,"Select probable foreground region.",1000);
    }

    void foregroundCallback(int state, void* userdata)
    {
        GUIData* gd = (GUIData*) userdata;
        gd->set(GUIData::Foreground);
        setMaskMouseCallback(*gd);
        cv::displayOverlay(gd->windowName,"Select sure foreground seeds.",1000);
    }

    void backgroundCallback(int state, void* userdata)
    {
        GUIData* gd = (GUIData*) userdata;
        gd->set(GUIData::Background);
        setMaskMouseCallback(*gd);
        cv::displayOverlay(gd->windowName,"Select sure background seeds.",1000);
    }

    void restartCallback(int state, void* userdata)
    {
        GUIData* gd = (GUIData*) userdata;
        gd->me()->restart();
        cv::displayOverlay(gd->windowName,"Current region has been restarted!",1000);
    }

    void saveCallback(int state, void* userdata)
    {
        GUIData* gd = (GUIData*) userdata;

        std::string bgMaskOutput = gd->outputFolder + "/mask-bg-" + std::to_string( gd->seedCounter ) + ".pgm";
        std::string fgMaskOutput = gd->outputFolder + "/mask-fg-" + std::to_string( gd->seedCounter ) + ".pgm";
        std::string pbfgMaskOutput = gd->outputFolder + "/mask-pbfg-" + std::to_string( gd->seedCounter ) + ".pgm";

        gd->set(GUIData::Background);
        cv::imwrite(bgMaskOutput,gd->me()->mask());
        restartCallback(0,gd);

        gd->set(GUIData::Foreground);
        cv::imwrite(fgMaskOutput,gd->me()->mask());
        restartCallback(0,gd);

        gd->set(GUIData::ProbablyForeground);
        cv::imwrite(pbfgMaskOutput,gd->me()->mask());
        restartCallback(0,gd);
        cv::displayOverlay(gd->windowName,"Regions successfuly saved!",1000);

        if(gd->once)
        {
            cv::destroyAllWindows();
            exit(1);
        }
    }
}