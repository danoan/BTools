#ifndef BTools_GUIDATA_H
#define BTools_GUIDATA_H

#include <boost/filesystem.hpp>
#include "MaskSelector.h"
#include "RectSelector.h"
#include "IMouseEvent.h"

namespace SeedSelector
{
    class GUIData
    {
    public:
        typedef SeedSelector::IMouseEvent IMouseEvent;
        typedef SeedSelector::MaskSelector::MouseEvent MaskMouseEvent;
        typedef SeedSelector::RectSelector::MouseEvent RectMouseEvent;

        enum MouseEventType{Foreground,Background,ProbablyForeground};

    private:
        GUIData(const std::string& windowName,
                const std::string& outputFolder,
                cv::Mat cvImg,
                bool once);

    public:
        static GUIData initGUIData(const std::string& windowName,
                                   const std::string& outputFolder,
                                   const std::string& imagePath,
                                   bool once);
        std::string windowName;
        std::string outputFolder;
        cv::Mat cvImg;
        bool once;
        unsigned char penWidth;
        unsigned int seedCounter;

        void loadPbFgMask(const std::string& pbfgMask);
        void loadFgMask(const std::string& fgMask);
        void loadBgMask(const std::string& bgMask);

        void set(MouseEventType met);
        void set(IMouseEvent* met);

        IMouseEvent* me();

    public:
        RectMouseEvent _meProbablyForeground;
        MaskMouseEvent _meForeground;
        MaskMouseEvent _meBackground;

        IMouseEvent* _meCurrent;
    };
}

#endif //BTools_GUIDATA_H
