#ifndef BTools_IMAGEDATAINPUT_H
#define BTools_IMAGEDATAINPUT_H

#include <DGtal/helpers/StdDefs.h>
#include <SCaBOliC/Energy/ISQ/Terms/Data/IProbabilityDistribution.h>
#include <opencv2/core/mat.hpp>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Transform.h>

namespace BTools
{
    namespace Core
    {
        struct ImageDataInput
        {
        public:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;


            typedef SCaBOliC::Energy::ISQ::IProbabilityDistribution<double> MyProbabilityDistribution;
            typedef cv::Mat cvColorImage;

        private:
            static DigitalSet computeInputDS(const cvColorImage& segResult, Point& pt, int initialBorder)
            {
                Domain tempDomain(Point(0,0),
                                  Point(segResult.cols-1,
                                        segResult.rows-1)
                );
                DigitalSet tempDS(tempDomain);

                //Convert inputImg to 1-channel grayscale image.
                cv::Mat grayscale(segResult.size(),
                                  segResult.type());
                if(segResult.type()!=CV_8UC1)
                    cv::cvtColor(segResult,grayscale,cv::COLOR_RGB2GRAY,1);
                else
                    grayscale = segResult;

                DIPaCUS::Representation::CVMatToDigitalSet(tempDS,
                                                           grayscale,
                                                           1);


                Point _p;
                tempDS.computeBoundingBox(pt,_p);

                pt -= Point(20+initialBorder,20+initialBorder);

                DigitalSet inputDS = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(tempDS, Point(20+initialBorder,20+initialBorder) );
                return inputDS;
            }

            static DigitalSet setPixelMask(const std::string& pixelMaskPath)
            {
                if(pixelMaskPath!="")
                {
                    cv::Mat m = cv::imread(pixelMaskPath,CV_8UC1);
                    DigitalSet ds( Domain( Point(0,0), Point(m.cols-1,m.rows-1) ) );
                    DIPaCUS::Representation::CVMatToDigitalSet(ds,m,1);
                    return ds;
                }
                else
                {
                    DigitalSet ds(Domain(Point(0,0),Point(1,1)));
                    return ds;
                }

            }

        private:
            Point _translation;

        public:
            ImageDataInput(const MyProbabilityDistribution& fgDistr,
                           const MyProbabilityDistribution& bgDistr,
                           const cvColorImage& baseImage,
                           const cvColorImage& segResult,
                           const std::string& pixelMaskPath="",
                           const int initialBorder=20):fgDistr(fgDistr),
                                                       bgDistr(bgDistr),
                                                       baseImage(baseImage),
                                                       segResult(segResult),
                                                       pixelMask(setPixelMask(pixelMaskPath)),
                                                       inputDS(computeInputDS(segResult,_translation,initialBorder)),
                                                       inputDomain(inputDS.domain()),
                                                       translation(_translation){}

        public:
            const MyProbabilityDistribution& fgDistr;
            const MyProbabilityDistribution& bgDistr;

            const cvColorImage baseImage;
            const cvColorImage segResult;
            const DigitalSet pixelMask;

            const DigitalSet inputDS;
            const Domain inputDomain;

            const Point translation;
        };
    }
}
#endif //BTools_IMAGEDATAINPUT_H
