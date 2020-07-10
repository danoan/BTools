#include "BTools/core/BCApplication.h"
#include "../../../ext-projects/cmake-build-release/include/SCaBOliC/Core/model/ODRModel.h"

using namespace BTools::Core;

BCApplication::BCApplication(BCOutput& bcOutput,
                             const BCInput& bcInput)
{
  BCOutput::EnergySolution& solution = bcOutput.energySolution;
  const ModelParameters& modelParameters = bcInput.modelParameters;
  const ImageData& imageData = bcInput.imageData;

  DigitalSet inputDS(imageData.inputDS->domain());
  DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT, 1);
  DIPaCUS::Morphology::dilate(inputDS,
                              *imageData.inputDS,
                              se,
                              modelParameters.initialDilation);

  BCOutput lastValidSolution(bcInput);


  ODRPixels odrPixels(modelParameters.radius,
                      modelParameters.gridStep,
                      modelParameters.levels,
                      modelParameters.levelDefinition,
                      SCaBOliC::Core::ODRModel::FourNeighborhood,
                      1);


  std::string windowName="IterationViewer";

  if(bcInput.displayEachIteration)
  {
    cv::namedWindow(windowName);
    cv::imshow(windowName,imageData.grabcutImage);
  }

  int nit=0;
  try
  {
    while(nit<bcInput.maxIterations)
    {
      BCControl(solution,
                bcInput,
                odrPixels,
                inputDS);

      inputDS.clear();
      inputDS.insert(solution.outputDS.begin(),solution.outputDS.end());

      prepareProductImage(bcOutput,
                          imageData);

      if(nit%5==0 && bcInput.showProgress)
        std::cout << nit << "/" << bcInput.maxIterations << std::endl;


      if(bcInput.displayEachIteration)
      {
        cv::imshow(windowName,bcOutput.bcImageOutput);
        cv::waitKey(10);
      }

      lastValidSolution = bcOutput;
      ++nit;
    }
  }catch(std::exception ex)
  {
    std::cerr << "Error in iteration " << nit << ". Saving current solution.\n";
  }

  if(bcInput.displayEachIteration)
  {
    std::cout << "The flow is done. Press any key to exit" << std::endl;
    cv::waitKey(0);
    cv::destroyWindow(windowName);
  }

  bcOutput = lastValidSolution;
  prepareProductImage(bcOutput,
                      imageData);
}


void BCApplication::prepareProductImage(BCOutput& bcOutput,
                                        const ImageData& imageData)
{
  const BCOutput::EnergySolution& solution = bcOutput.energySolution;

  DigitalSet translatedBackDS( Domain( Point(0,0),
                                       Point(imageData.inputImage.cols-1,
                                             imageData.inputImage.rows-1)
  ) );

  for (auto it = solution.outputDS.begin(); it != solution.outputDS.end(); ++it)
  {
    Point pt = *it + imageData.translation;
    if( translatedBackDS.domain().isInside(pt) )
      translatedBackDS.insert(pt);
  }

  cv::Mat foregroundMask = cv::Mat::zeros(imageData.inputImage.size(),
                                          CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask,translatedBackDS);

  BTools::Utils::setHighlightMask(bcOutput.bcImageOutput,imageData.inputImage,foregroundMask);

}
