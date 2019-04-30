#ifndef BTOOLS_APPLICATION_FLOWCONTROL_H
#define BTOOLS_APPLICATION_FLOWCONTROL_H

#include <ostream>

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>


#include <SCaBOliC/Utils/Utils.h>
#include <DIPaCUS/base/Representation.h>

#include <BinOCS/core/model/input/ODRConfigInput.h>
#include <BinOCS/core/model/input/BCApplicationInput.h>
#include <BinOCS/core/model/input/BCFlowInput.h>
#include <BinOCS/core/model/input/BCConfigInput.h>
#include <BinOCS/core/model/input/ImageDataInput.h>
#include <BinOCS/core/model/BCAOutput.h>
#include <BinOCS/core/BCApplication.h>
#include <BinOCS/utils/imgUtils.h>
#include <BinOCS/utils/strUtils.h>

#include "model/MockDistribution.h"
#include "model/Types.h"
#include "control/DataWriter.h"


namespace ShapeFlow
{
    class FlowControl
    {
    public:
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::Space Space;
        typedef DGtal::Z2i::Domain Domain;

        typedef DGtal::Shapes<Domain> Shapes;
        typedef DIPaCUS::Representation::Image2D Image2D;

        typedef BinOCS::Core::ODRConfigInput ODRConfigInput;
        typedef BinOCS::Core::BCApplicationInput BCAInput;
        typedef BinOCS::Core::BCConfigInput BCConfigInput;
        typedef BinOCS::Core::ImageDataInput ImageDataInput;
        typedef BinOCS::Core::BCFlowInput BCFlowInput;
        typedef BinOCS::Core::BCApplicationOutput BCAOutput;
        typedef BCAOutput::EnergySolution EnergySolution;

        typedef DataWriter::TableEntry TableEntry;


    public:
        FlowControl(const BCFlowInput& bcFlowInput,
                    Shape  shape,
                    const std::string& outputFolder,
                    std::ostream& osLog);

    private:
        DigitalSet resolveShape(Shape shape);

        std::vector<TableEntry> initEntries(const DigitalSet& ds);
        BCAOutput boundaryCorrection(const BCFlowInput& bcFlowInput,
                                     const cv::Mat& currentImage,
                                     Point& translation);
        DigitalSet correctTranslation(const BCAOutput::EnergySolution& solution,
                                      const cv::Mat& currentImage,
                                      const Point& translation);
        void checkBounds(const DigitalSet& ds, const Domain& domain);

        void shapeFlow(const DigitalSet& _ds,
                       const BCFlowInput& bcFlowInput,
                       const std::string& outputFolder,
                       std::ostream& osLog);
    };
}

#endif //BTOOLS_APPLICATION_FLOWCONTROL_H
