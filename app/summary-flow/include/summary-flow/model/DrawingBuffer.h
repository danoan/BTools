#ifndef BTOOLS_SUMMARY_FLOW_DRAWINGBUFFER_H
#define BTOOLS_SUMMARY_FLOW_DRAWINGBUFFER_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

namespace SummaryFlow
{
    class DrawingBuffer
    {
    private:
        typedef DGtal::Board2D Board2D;

    public:
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Color Color;

    public:
        DrawingBuffer(){};
        DrawingBuffer(const Domain& domain);
        void draw(const DigitalSet& ds,const Color& fillColor,const Color& contourColor);
        void draw(const Point& p,const Color& fillColor,const Color& contourColor);

        void flushSVG(const std::string& imageOutputPath);
        void flushEPS(const std::string& imageOutputPath);

    private:
        Board2D board;
    };
}

#endif //BTOOLS_SUMMARY_FLOW_DRAWINGBUFFER_H
