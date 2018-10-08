#ifndef BTOOLS_APPLICATION_ILLUSTRATION_AROUNDBOUNDARYREASONING_H
#define BTOOLS_APPLICATION_ILLUSTRATION_AROUNDBOUNDARYREASONING_H

#include <boost/filesystem/operations.hpp>

#include "DGtal/shapes/ShapeFactory.h"
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/shapes/GaussDigitizer.h>
#include <DGtal/shapes/CDigitalBoundedShape.h>

#include <DIPaCUS/derivates/Misc.h>
#include <DGtal/io/boards/Board2D.h>

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
            class AroundBoundaryReasoning
            {
            public:
                typedef DGtal::Z2i::Space MySpace;
                typedef DGtal::NGon2D<MySpace> MyNGon2D;
                typedef DGtal::GaussDigitizer<MySpace,MyNGon2D> MyGaussDigitizer;
                typedef DGtal::Z2i::Domain Domain;
                typedef DGtal::Z2i::Point Point;
                typedef DGtal::Z2i::DigitalSet DigitalSet;
            public:
                AroundBoundaryReasoning(const std::string& outputFolder);
            private:
                template<typename TDigitalBoundedShape>
                void topLeftCorner(Point& tlc, TDigitalBoundedShape& digitalSet);

                int createAndSavePicture(int radius,
                                          const Point &center,
                                          const DigitalSet &baseSet,
                                          const std::string &outputFilePath);

                void createFromListOfCenter(Point listOfCenter[],
                                            int radius,
                                            const DigitalSet& dsBase,
                                            const std::string& outputPrefix);

            public:
                int t;
            };
        }
    }
}

#include "AroundBoundaryReasoning.hpp"

#endif //BTOOLS_APPLICATION_ILLUSTRATION_AROUNDBOUNDARYREASONING_H
