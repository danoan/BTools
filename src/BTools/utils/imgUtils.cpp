#include "BTools/utils/imgUtils.h"

using namespace BTools;

cv::Rect Utils::computeBoundingBox(const cv::Mat &img)
{
    int nRows = img.rows;
    int nCols = img.cols;


    cv::Point low,high;
    low = cv::Point(10000,10000);
    high = cv::Point(0,0);

    typedef cv::Vec3b ColorType;

    const ColorType* row;
    for(int i=0;i<nRows;++i)
    {
        row = img.ptr<ColorType>(i);
        for(int j=0;j<nCols;++j)
        {
            if(row[j]==ColorType(0,0,0)) continue;

            low.x = j<low.x?j:low.x;
            low.y = i<low.y?i:low.y;

            high.x = j>high.x?j:high.x;
            high.y = i>high.y?i:high.y;
        }
    }

    return cv::Rect(low,high);
}

void Utils::setHighlightedBorder(cv::Mat &img, Utils::ColorType color)
{
    std::cout << "Highlight!" << std::endl;

    cv::Mat dilated = img.clone();
    cv::dilate(img,dilated,cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(1,1)));

    cv::Mat imgFilter = cv::Mat::zeros(img.size(),CV_8UC1);
    cv::cvtColor(img,imgFilter,cv::COLOR_BGRA2GRAY);

    dilated.setTo(0,imgFilter);

    cv::Mat dilatedFilter = cv::Mat::zeros(dilated.size(),CV_8UC1);
    cv::cvtColor(dilated,dilatedFilter,cv::COLOR_BGRA2GRAY);
    img.setTo(color,dilatedFilter);
}