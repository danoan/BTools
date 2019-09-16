#include "BTools/core/BCApplication.h"
#include "../../../jmiv-figures/fig8-9/include/energyUtils.h"

using namespace BTools::Core;

BCApplication::BCApplication(BCAOutput& bcaOutput,
                             const BCAInput& bcaInput,
                             int maxIterations,
                             bool displayEachIteration)
{
    BCAOutput::EnergySolution& solution = bcaOutput.energySolution;

    DigitalSet inputDS(bcaInput.imageDataInput.inputDS.domain());
    DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT, 1);
    DIPaCUS::Morphology::dilate(inputDS,bcaInput.imageDataInput.inputDS,se,bcaInput.bcConfigInput.initialDilation);

    BCAOutput lastValidSolution(bcaInput);

    const ODRConfigInput& odrInput = bcaInput.odrConfigInput;
    ODRPixels odrPixels(odrInput.radius,
                        odrInput.gridStep,
                        odrInput.levels,
                        odrInput.levelDefinition,
                        odrInput.neighborhood);


    std::string windowName="IterationViewer";
    if(displayEachIteration)
    {
        cv::namedWindow(windowName);
        cv::imshow(windowName,bcaInput.imageDataInput.segResult);
    }

    int nit=0;
    try
    {
        while(nit<maxIterations)
        {
            BCControl(solution,
                      bcaInput,
                      odrPixels,
                      inputDS);

            inputDS.clear();
            inputDS.insert(solution.outputDS.begin(),solution.outputDS.end());

            prepareProductImage(bcaOutput,
                                bcaInput.imageDataInput);

            if(nit%5==0 && bcaInput.showProgress)
                std::cout << nit << "/" << maxIterations << std::endl;


            if(displayEachIteration)
            {
                cv::imshow(windowName,bcaOutput.imgOutput);
                cv::waitKey(10);
            }

            lastValidSolution = bcaOutput;
            ++nit;
        }
    }catch(std::exception ex)
    {
        std::cerr << "Error in iteration " << nit << ". Saving current solution.\n";
    }

    if(displayEachIteration)
    {
        std::cout << "Flow is done. Press any key to exit" << std::endl;
        cv::waitKey(0);
        cv::destroyWindow(windowName);
    }

    bcaOutput = lastValidSolution;
    prepareProductImage(bcaOutput,
                        bcaInput.imageDataInput);
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
