#ifndef BINOCS_GUICONTROL_H
#define BINOCS_GUICONTROL_H

#include "GUIData.h"

namespace SeedSelector
{
    void setRectMouseCallback(GUIData& gd);
    void setMaskMouseCallback(GUIData& gd);


    void displayStatusBar(const GUIData& gd);
    void refreshWindow(GUIData& gd);


    void probablyForegroundCallback(int state, void* userdata);
    void foregroundCallback(int state, void* userdata);
    void backgroundCallback(int state, void* userdata);
    void restartCallback(int state, void* userdata);
    void saveCallback(int state, void* userdata);
}

#endif //BINOCS_GUICONTROL_H
