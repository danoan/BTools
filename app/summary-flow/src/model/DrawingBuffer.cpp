#include "summary-flow/model/DrawingBuffer.h"

namespace SummaryFlow
{
    DrawingBuffer::DrawingBuffer(const Domain& domain)
    {
        board << DGtal::SetMode(domain.className(), "Grid" );
        board << domain;
    }

    void DrawingBuffer::draw(const DigitalSet& ds,const Color& fillColor,const Color& contourColor)
    {
        board << DGtal::CustomStyle( ds.className(),
                                     new DGtal::CustomColors(fillColor,contourColor) )
              << ds;
    }

    void DrawingBuffer::draw(const Point& point,const Color& fillColor,const Color& contourColor)
    {
        board << DGtal::CustomStyle( point.className(),
                                     new DGtal::CustomColors(fillColor,contourColor) )
              << point;
    }

    void DrawingBuffer::flushSVG(const std::string& imageOutputPath)
    {
        board.saveSVG( (imageOutputPath).c_str(),200,200,10 );
    }

    void DrawingBuffer::flushEPS(const std::string& imageOutputPath)
    {
        board.saveEPS( (imageOutputPath).c_str(),200,200,10 );
    }
}