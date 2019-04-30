#ifndef BINOCS_IMAGEDATAINPUT_H
#define BINOCS_IMAGEDATAINPUT_H

#include <DGtal/helpers/StdDefs.h>
#include <SCaBOliC/Energy/ISQ/Terms/Data/IProbabilityDistribution.h>
#include <opencv2/core/mat.hpp>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Transform.h>

namespace BinOCS
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
            static DigitalSet computeInputDS(const cvColorImage& segResult, Point& pt)
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

                pt -= Point(20,20);

                DigitalSet inputDS = DIPaCUS::Transform::bottomLeftBoundingBoxAtOrigin(tempDS, Point(20,20) );
                return inputDS;
            }

        private:
            Point _translation;

        public:
            ImageDataInput(const MyProbabilityDistribution& fgDistr,
                           const MyProbabilityDistribution& bgDistr,
                           const cvColorImage& baseImage,
                           const cvColorImage& segResult):fgDistr(fgDistr),
                                                          bgDistr(bgDistr),
                                                          baseImage(baseImage),
                                                          segResult(segResult),
                                                          inputDS(computeInputDS(segResult,_translation)),
                                                          inputDomain(inputDS.domain()),
                                                          translation(_translation){}

        public:
            const MyProbabilityDistribution& fgDistr;
            const MyProbabilityDistribution& bgDistr;

            const cvColorImage baseImage;
            const cvColorImage segResult;

            const DigitalSet inputDS;
            const Domain inputDomain;

            const Point translation;
        };
    }
}
#endif //BINOCS_IMAGEDATAINPUT_H
