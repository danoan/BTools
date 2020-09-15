#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <boost/filesystem.hpp>

#include <SCaBOliC/Utils/Utils.h>

#include "BTools/api/api.h"

#include "BTools/core/model/input/ModelParameters.h"
#include "BTools/core/model/input/ImageData.h"
#include "BTools/core/model/input/BCInput.h"
#include "BTools/core/model/CVMatDistribution.h"

#include "BTools/io/seed/GrabCutObject.h"
#include "BTools/utils/imgUtils.h"
#include "BTools/utils/timer.h"

#include "InputReader.h"


using namespace BTools::Core;
using namespace DGtal::Z2i;

using namespace BoundaryCorrection;
using namespace BTools::IO::Seed;

typedef SCaBOliC::Energy::Solution EnergySolution;

void initGMMs( const cv::Mat& img, const cv::Mat& mask, GMM& bgdGMM, GMM& fgdGMM )
{
  const int kMeansItCount = 10;
  const int kMeansType = cv::KMEANS_PP_CENTERS;

  cv::Mat bgdLabels, fgdLabels;
  std::vector<cv::Vec3f> bgdSamples, fgdSamples;
  cv::Point p;
  for( p.y = 0; p.y < img.rows; p.y++ )
  {
    for( p.x = 0; p.x < img.cols; p.x++ )
    {
      if( mask.at<uchar>(p) == cv::GC_BGD || mask.at<uchar>(p) == cv::GC_PR_BGD )
        bgdSamples.push_back( (cv::Vec3f)img.at<cv::Vec3b>(p) );
      else // GC_FGD | GC_PR_FGD
        fgdSamples.push_back( (cv::Vec3f)img.at<cv::Vec3b>(p) );
    }
  }

  cv::Mat _bgdSamples( (int)bgdSamples.size(), 3, CV_32FC1, &bgdSamples[0][0] );
  cv::kmeans( _bgdSamples, GMM::componentsCount, bgdLabels,
              cv::TermCriteria( cv::TermCriteria::MAX_ITER, kMeansItCount, 0.0), 0, kMeansType );

  cv::Mat _fgdSamples( (int)fgdSamples.size(), 3, CV_32FC1, &fgdSamples[0][0] );
  cv::kmeans( _fgdSamples, GMM::componentsCount, fgdLabels,
              cv::TermCriteria( cv::TermCriteria::MAX_ITER, kMeansItCount, 0.0), 0, kMeansType );

  bgdGMM.initLearning();
  for( int i = 0; i < (int)bgdSamples.size(); i++ )
    bgdGMM.addSample( bgdLabels.at<int>(i,0), bgdSamples[i] );
  bgdGMM.endLearning();

  fgdGMM.initLearning();
  for( int i = 0; i < (int)fgdSamples.size(); i++ )
    fgdGMM.addSample( fgdLabels.at<int>(i,0), fgdSamples[i] );
  fgdGMM.endLearning();
}


void outputImages(const BCInput& bcInput, const EnergySolution& solution, const GrabCutObject& gco, const std::string& outputFolder)
{
  std::string graphCutSegFilepath = outputFolder + "/gc-seg.png";
  std::string correctedSegFilepath = outputFolder +"/corrected-seg.png";
  std::string maskBoundaryFilepath = outputFolder +"/mask-seg.png";


  cv::Mat gcSegImg = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
  BTools::Utils::setHighlightMask(gcSegImg,gco.inputImage,gco.segMask);

  cv::Mat bcImage = BTools::Core::createBCImage(solution.outputDS,bcInput.imageData);

  int sx = bcInput.imageData.translation[0];
  int sy = bcInput.imageData.translation[1];

  cv::Mat segMask = cv::Mat::zeros(gco.inputImage.size(),CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(segMask,solution.outputDS,sx,sy);

  cv::imwrite(graphCutSegFilepath,gcSegImg);
  cv::imwrite(correctedSegFilepath,bcImage);
  cv::imwrite(maskBoundaryFilepath,segMask);
}

void outputEnergy(const BCInput& bcInput, const EnergySolution& solution,const GrabCutObject& gco, const std::string& outputFolder)
{
  const ModelParameters& modelParameters = bcInput.modelParameters;
  const ImageData& imageData = bcInput.imageData;

  double outputElasticaEnergy,inputElasticaEnergy;

  SCaBOliC::Utils::ISQEvaluation::IICurvatureExtraData extraData(true,modelParameters.radius);
  inputElasticaEnergy = SCaBOliC::Utils::ISQEvaluation::ii(*imageData.inputDS,1.0,modelParameters.lengthTermWeight,modelParameters.sqTermWeight,&extraData);
  outputElasticaEnergy = SCaBOliC::Utils::ISQEvaluation::ii(solution.outputDS,1.0,modelParameters.lengthTermWeight,modelParameters.sqTermWeight,&extraData);

  cv::Mat gcSegImage = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
  gco.inputImage.copyTo(gcSegImage ,gco.segMask);

  cv::Mat grayImage(gcSegImage.size(),CV_8UC1);
  cv::cvtColor(gcSegImage,grayImage,cv::ColorConversionCodes::COLOR_BGR2GRAY);


  std::ofstream ofs(outputFolder + "/energy.txt");
  ofs << "GrabCut Segmentation Elastica Energy: " << inputElasticaEnergy << "\n"
      << "Boundary Correction Elastica Energy: " << outputElasticaEnergy << std::endl;

  ofs << "#Execution time: ";
  BTools::Utils::Timer::end(ofs);
  ofs.close();
}

struct ExtParams{

  ExtParams(const GrabCutObject& gco, std::ostream& osLog, const std::string& outputFolder)
      :gco(gco),
       osLog(osLog),
       outputFolder(outputFolder){}

  const GrabCutObject& gco;
  std::string outputFolder;

  std::ostream& osLog;
};


void callback( BTools::API::CallbackData&& data, ExtParams& extParams ){

  switch(data.event){
    case BTools::API::Event::Start:
      BTools::Utils::Timer::start();
      break;
    case BTools::API::Event::Iteration:
      if(data.iteration%5==0 && data.bcInput.showProgress){
        extParams.osLog << data.iteration << "/" << data.bcInput.maxIterations << "\n";
      }

      if(data.bcInput.displayEachIteration)
      {
        cv::Mat bcImage = BTools::Core::createBCImage(data.solution.outputDS,data.bcInput.imageData);
        cv::imshow(data.windowName,bcImage);
        cv::waitKey(10);
      }
      break;
    case BTools::API::Event::End:
      BTools::Utils::Timer::end(extParams.osLog);
      if(data.bcInput.displayEachIteration){
        extParams.osLog << "The flow is done. Press any key to exit\n";
        cv::waitKey(0);
      }

      if(extParams.outputFolder!="")
      {
        boost::filesystem::create_directories(extParams.outputFolder);
        outputImages(data.bcInput, data.solution,extParams.gco,extParams.outputFolder);
        outputEnergy(data.bcInput, data.solution,extParams.gco,extParams.outputFolder);
      }

      break;
  }

}

int main(int argc, char* argv[])
{
  InputReader::InputData inputData = InputReader::readInput(argc,argv);

  GrabCutObject gco = read(inputData.grabcutFile);
  ModelParameters modelParameters(inputData.radius,
                                  1.0,
                                  inputData.levels,
                                  inputData.levelDefinition,
                                  inputData.dtWeight,
                                  inputData.sqWeight,
                                  inputData.lgWeight,
                                  inputData.initialDilation);

  cv::Mat segResultImg = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
  gco.inputImage.copyTo(segResultImg,gco.segMask);

  cv::Mat fgModel,bgModel;
  GMM fgGMM(fgModel),bgGMM(bgModel);
  initGMMs(gco.inputImage,gco.grabCutMask,bgGMM,fgGMM);

  CVMatDistribution fgDistr(gco.inputImage,fgGMM);
  CVMatDistribution bgDistr(gco.inputImage,bgGMM);

  ImageData imageData(fgDistr,
                      bgDistr,
                      gco.inputImage,
                      segResultImg,
                      2*(2*inputData.radius+inputData.initialDilation));

  BCInput bcInput(modelParameters,
                  imageData,
                  inputData.iterations,
                  inputData.showIterations,
                  inputData.showProgress);


  ExtParams extParams(gco,std::cout,inputData.outputFolder);
  BTools::API::bce(bcInput,
                   [&extParams](BTools::API::CallbackData&& data){ callback(std::move(data),extParams); } );

}
