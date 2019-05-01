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
        translatedBackDS.insert(*it + imageDataInput.translation );

    cv::Mat outputMask = cv::Mat::zeros(imageDataInput.baseImage.size(),
                                        CV_8UC1);

    DIPaCUS::Representation::digitalSetToCVMat(outputMask,translatedBackDS);


    bcaOutput.imgOutput = cv::Mat::zeros(imageDataInput.baseImage.size(),
                                         imageDataInput.baseImage.type());


    imageDataInput.baseImage.copyTo(bcaOutput.imgOutput,
                                    outputMask);
}


