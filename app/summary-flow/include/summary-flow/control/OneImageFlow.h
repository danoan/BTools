#ifndef BTOOLS_APPLICATION_FLOW_ONEIMAGEFLOW_H
#define BTOOLS_APPLICATION_FLOW_ONEIMAGEFLOW_H

#include <functional>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>
#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/base/Representation.h>

#include "summary-flow/model/DrawingBuffer.h"
#include "summary-flow/model/ColorScheme.h"
#include "summary-flow/utils.h"
#include "summary-flow/types.h"

namespace SummaryFlow
{
    class OneImageFlow
    {
    public:
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Point Point;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::SCell SCell;
        typedef DGtal::Color Color;
        typedef DGtal::Board2D Board2D;

        typedef std::set<Point> SetPoint;
        typedef std::vector< SetPoint > SetPointSequence;

        typedef DIPaCUS::Representation::Image2D Image2D;
        typedef DIPaCUS::Neighborhood::EightNeighborhoodPredicate Pred8;
        

    public:
        OneImageFlow(const std::string& imageSrcFolder,
                     const std::string& imageOutputPath,
                     const std::string& imageExtension,
                     int drawInterval,
                     const ColorScheme& colorScheme,
                     ImageOutputType iot,
                     const std::string& pixelMaskPath,
                     const std::string& dirsMaskPath,
                     bool drawCenterBall,
                     double radius,
                     double h);

    private:
        void collectImagesPath(std::vector<std::string>& paths,
                const std::string& imageSrcFolder,
                const std::string& imageExtension,
                std::function<bool(const std::string&)> validPath);

        void extractContourPoints( SetPointSequence& contours,
                                   const std::string& imagePath,
                                   const SetPoint& fixedPixels);

        SetPoint setFromMask(const std::string& imgPath);
        Domain findCommonDomain(const SetPointSequence& contours);

        void drawContours(DrawingBuffer& drawBuffer,
                          const SetPointSequence& contours,
                          int drawInterval,
                          const ColorScheme& colorScheme);

        void createUnifiedImage(const std::string& imgOutputPath,
                                const SetPointSequence& contours,
                                const std::set<Point>& extraPoints,
                                const ColorScheme& colorScheme,
                                int drawInterval,
                                ImageOutputType iot);
    };

}

#endif //BTOOLS_APPLICATION_FLOW_ONEIMAGEFLOW_H
