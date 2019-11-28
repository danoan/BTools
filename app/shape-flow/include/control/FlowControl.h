#ifndef BTOOLS_APPLICATION_FLOWCONTROL_H
#define BTOOLS_APPLICATION_FLOWCONTROL_H

#include <ostream>

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>


#include <SCaBOliC/Utils/Utils.h>
#include <DIPaCUS/base/Representation.h>

#include <BTools/core/model/input/ODRConfigInput.h>
#include <BTools/core/model/input/BCApplicationInput.h>
#include <BTools/core/model/input/BCConfigInput.h>
#include <BTools/core/model/input/ImageDataInput.h>
#include <BTools/core/model/BCAOutput.h>
#include <BTools/core/BCApplication.h>

#include <BTools/utils/imgUtils.h>
#include <BTools/utils/strUtils.h>
#include <BTools/utils/timer.h>

#include <BTools/reader/Types.h>

#include "model/MockDistribution.h"
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

        typedef BTools::Core::ODRConfigInput ODRConfigInput;
        typedef BTools::Core::BCConfigInput BCConfigInput;
        typedef BTools::Core::BCApplicationOutput BCAOutput;
        typedef BCAOutput::EnergySolution EnergySolution;

        typedef BTools::Reader::DCFReader::Shape Shape;
        typedef BTools::Reader::DCFReader::ShapeType ShapeType;

        typedef DataWriter::TableEntry TableEntry;


    public:
        FlowControl(const BCConfigInput& bcInput,
                    const ODRConfigInput& odrConfigInput,
                    int iterations,
                    Shape  shape,
                    double gridStep,
                    const std::string& pixelMaskFilepath,
                    const std::string& outputFolder,
                    std::ostream& osLog);

    private:
        DigitalSet resolveShape(Shape shape,double gridStep);

        std::vector<TableEntry> initEntries(const ODRConfigInput& odrConfigInput, const DigitalSet& ds);
        BCAOutput boundaryCorrection(const BCConfigInput& bcInput,
                                     const ODRConfigInput& odrConfigInput,
                                     const std::string& pixelMaskFilepath,
                                     const cv::Mat& currentImage,
                                     Point& translation);

        DigitalSet correctTranslation(const BCAOutput::EnergySolution& solution,
                                      const cv::Mat& currentImage,
                                      const Point& translation);

        void checkBounds(const DigitalSet& ds, const Domain& domain);

        void shapeFlow(const DigitalSet& _ds,
                       int maxIterations,
                       const std::string& inputName,
                       const BCConfigInput& bcConfigInput,
                       const ODRConfigInput& odrConfigInput,
                       const std::string& pixelMaskFilepath,
                       const std::string& outputFolder,
                       std::ostream& osLog);
    };
}

#endif //BTOOLS_APPLICATION_FLOWCONTROL_H
