#include "BTools/api/api.h"

namespace BTools{
namespace API{
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef SCaBOliC::Core::ODRPixels ODRPixels;

typedef BTools::Core::ModelParameters ModelParameters;
typedef BTools::Core::ImageData ImageData;


void bce(const BCInput& bcInput,BCECallback callback)
{
  const ModelParameters& modelParameters = bcInput.modelParameters;
  const ImageData& imageData = bcInput.imageData;
  EnergySolution solution(imageData.inputDomain);

  DigitalSet inputDS(imageData.inputDS->domain());
  DIPaCUS::Morphology::StructuringElement se(DIPaCUS::Morphology::StructuringElement::RECT, 1);
  DIPaCUS::Morphology::dilate(inputDS,*imageData.inputDS,se,modelParameters.initialDilation);

  ODRPixels odrPixels(modelParameters.radius,
                      modelParameters.gridStep,
                      modelParameters.levels,
                      modelParameters.levelDefinition,
                      SCaBOliC::Core::ODRModel::FourNeighborhood,
                      1);


  std::string windowName="IterationViewer";
  if(bcInput.displayEachIteration){
    cv::namedWindow(windowName);
  }

  callback( CallbackData{Event::Start,0,windowName,bcInput,solution} );

  int nit=0;
  try{
    while(nit<bcInput.maxIterations){
      BTools::Core::solveModel(solution,
                               bcInput,
                               odrPixels,
                               inputDS);
      ++nit;
      callback( CallbackData{Event::Iteration,nit,windowName,bcInput,solution} );

      inputDS.clear();
      inputDS.insert(solution.outputDS.begin(),solution.outputDS.end());


    }
  }catch(std::exception ex){
    std::cerr << "Error in iteration " << nit << ". Saving current solution.\n";
  }

  callback( CallbackData{Event::End,nit,windowName,bcInput,solution} );
}


}
}