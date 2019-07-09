#include "BTools/core/BCApplication.h"

using namespace BTools::Core;

BCApplication::BCApplication(BCAOutput& bcaOutput,
                             const BCAInput& bcaInput,
                             int maxIterations,
                             bool displayEachIteration)
{
    std::vector< IBCControlVisitor* > mock;
    
    BCApplication(bcaOutput,bcaInput,maxIterations,displayEachIteration,mock.begin(),mock.end());
}


void BCApplication::prepareProductImage(BCAOutput& bcaOutput,
                                        const ImageDataInput& imageDataInput)
{
    const BCAOutput::EnergySolution& solution = bcaOutput.energySolution;
    DigitalSet translatedBackDS( Domain( Point(0,0),
                                         Point(imageDataInput.baseImage.cols-1,
                                               imageDataInput.baseImage.rows-1)
    ) );

    for (auto it = solution.outputDS.begin(); it != solution.outputDS.end(); ++it)
    {
        Point pt = *it + imageDataInput.translation;
        if( translatedBackDS.domain().isInside(pt) )
            translatedBackDS.insert(pt);
    }

    cv::Mat foregroundMask = cv::Mat::zeros(imageDataInput.baseImage.size(),
                                            CV_8UC1);
    DIPaCUS::Representation::digitalSetToCVMat(foregroundMask,translatedBackDS);

    BTools::Utils::setHighlightMask(bcaOutput.imgOutput,imageDataInput.baseImage,foregroundMask);


}
