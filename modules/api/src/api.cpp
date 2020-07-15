#include "BTools/api/api.h"

namespace BTools{
namespace API{
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef SCaBOliC::Core::ODRPixels ODRPixels;

typedef BTools::Core::ModelParameters ModelParameters;
typedef BTools::Core::ImageData ImageData;


void bce(BCOutput& bcOutput, const BCInput& bcInput)
{
  BCOutput::EnergySolution& solution = bcOutput.energySolution;
  const ModelParameters& modelParameters = bcInput.modelParameters;
  const ImageData& imageData = bcInput.imageData;

  DigitalSet inputDS(imageData.inputDS->domain());
  DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT, 1);
  DIPaCUS::Morphology::dilate(inputDS,*imageData.inputDS,se,modelParameters.initialDilation);

  BCOutput lastValidSolution(bcInput);


  ODRPixels odrPixels(modelParameters.radius,
                      modelParameters.gridStep,
                      modelParameters.levels,
                      modelParameters.levelDefinition,
                      SCaBOliC::Core::ODRModel::FourNeighborhood,
                      1);


  std::string windowName="IterationViewer";

  if(bcInput.displayEachIteration){
    cv::namedWindow(windowName);
    cv::imshow(windowName,imageData.grabcutImage);
  }

  int nit=0;
  try{
    while(nit<bcInput.maxIterations){
      BTools::Core::solveModel(solution,
                               bcInput,
                               odrPixels,
                               inputDS);

      inputDS.clear();
      inputDS.insert(solution.outputDS.begin(),solution.outputDS.end());

      BTools::Core::createBCImage(bcOutput,
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
  }catch(std::exception ex){
    std::cerr << "Error in iteration " << nit << ". Saving current solution.\n";
  }

  if(bcInput.displayEachIteration){
    std::cout << "The flow is done. Press any key to exit" << std::endl;
    cv::waitKey(0);
    cv::destroyWindow(windowName);
  }

  bcOutput = lastValidSolution;
  BTools::Core::createBCImage(bcOutput,
                              imageData);
}


}
}