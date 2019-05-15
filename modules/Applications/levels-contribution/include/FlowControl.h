#ifndef BTOOLS_APPLICATION_MOSTEXTERN_FLOWCONTROL_H
#define BTOOLS_APPLICATION_MOSTEXTERN_FLOWCONTROL_H

#include <ostream>

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>


#include <SCaBOliC/Utils/Utils.h>
#include <DIPaCUS/base/Representation.h>

#include "BTools/core/model/input/ODRConfigInput.h"
#include "BTools/core/model/input/BCApplicationInput.h"
#include "BTools/core/model/input/BCFlowInput.h"
#include "BTools/core/model/input/BCConfigInput.h"
#include "BTools/core/model/input/ImageDataInput.h"
#include "BTools/core/model/BCAOutput.h"
#include "BTools/core/BCApplication.h"
#include "BTools/utils/imgUtils.h"
#include "BTools/utils/strUtils.h"
#include "BTools/visitors/PotentialMap.h"

#include "MockDistribution.h"
#include "Types.h"


namespace MostExternContribution
{
    class FlowControl
    {
    public:
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Space Space;
        typedef DGtal::Z2i::Domain Domain;

        typedef DGtal::Shapes<Domain> Shapes;
        typedef DIPaCUS::Representation::Image2D Image2D;

        typedef BTools::Core::ODRConfigInput ODRConfigInput;
        typedef BTools::Core::BCApplicationInput BCAInput;
        typedef BTools::Core::BCConfigInput BCConfigInput;
        typedef BTools::Core::ImageDataInput ImageDataInput;
        typedef BTools::Core::BCFlowInput BCFlowInput;
        typedef BTools::Core::BCApplicationOutput BCAOutput;
        typedef BCAOutput::EnergySolution EnergySolution;


    public:
        FlowControl(const BCFlowInput& bcFlowInput,
                    Shape  shape,
                    double gridStep,
                    const std::string& outputFolder,
                    bool ignoreOptIntersection,
                    std::ostream& osLog);

    private:
        DigitalSet resolveShape(Shape shape,double gridStep);
        void createMostExternContributionFigure(const BCAInput& bcaInput,
                const std::string& outputPath, bool ignoreOptIntersection);

        BCAOutput boundaryCorrection(const BCFlowInput& bcFlowInput,
                                     const cv::Mat& currentImage,
                                     const std::string& outputFolder,
                                     const std::string& suffix,
                                     bool ignoreOptIntersection,
                                     Point& translation);

        DigitalSet correctTranslation(const BCAOutput::EnergySolution& solution,
                                      const cv::Mat& currentImage,
                                      const Point& translation);
        void checkBounds(const DigitalSet& ds, const Domain& domain);

        void shapeFlow(const DigitalSet& _ds,
                       const BCFlowInput& bcFlowInput,
                       const std::string& outputFolder,
                       bool ignoreOptIntersection,
                       std::ostream& osLog);
    };
}

#endif //BTOOLS_APPLICATION_MOSTEXTERN_FLOWCONTROL_H
