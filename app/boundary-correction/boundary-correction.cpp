#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <boost/filesystem.hpp>

#include <SCaBOliC/Utils/Utils.h>

#include "BTools/api/api.h"

#include "BTools/core/model/input/ModelParameters.h"
#include "BTools/core/model/input/ImageData.h"
#include "BTools/core/model/input/BCInput.h"
#include "BTools/core/model/BCOutput.h"
#include "BTools/core/model/CVMatDistribution.h"

#include "BTools/io/seed/GrabCutObject.h"
#include "BTools/utils/imgUtils.h"
#include "BTools/utils/timer.h"

#include "InputReader.h"


using namespace BTools::Core;
using namespace DGtal::Z2i;

using namespace BoundaryCorrection;
using namespace BTools::IO::Seed;

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


cv::Mat highlightBorder(const DigitalSet& ds, const cv::Vec3b& color=cv::Vec3b(255,255,255))
{
  const DigitalSet& boundaryMaskDs = ds;
  Point dims = boundaryMaskDs.domain().upperBound() - boundaryMaskDs.domain().lowerBound() + Point(1,1);
  cv::Mat maskBoundaryImgGS = cv::Mat::zeros( dims(1),dims(0) ,CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(maskBoundaryImgGS,boundaryMaskDs);

  cv::Mat maskBoundaryImgColor( maskBoundaryImgGS.size(),CV_8UC3);
  cv::cvtColor(maskBoundaryImgGS,maskBoundaryImgColor,cv::COLOR_GRAY2RGB);

  BTools::Utils::setHighlightedBorder(maskBoundaryImgColor,color);
  return maskBoundaryImgColor;
}

void outputImages(const BCOutput& bcOutput, const GrabCutObject& gco, const std::string& outputFolder)
{
  const BCOutput::EnergySolution& solution = bcOutput.energySolution;

  std::string graphCutSegFilepath = outputFolder + "/gc-seg.png";
  std::string correctedSegFilepath = outputFolder +"/corrected-seg.png";
  std::string maskBoundaryFilepath = outputFolder +"/mask-boundary.png";


  cv::Mat gcSegImg = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
  BTools::Utils::setHighlightMask(gcSegImg,gco.inputImage,gco.segMask);


  cv::imwrite(graphCutSegFilepath,gcSegImg);
  cv::imwrite(correctedSegFilepath,bcOutput.bcImageOutput);
  cv::imwrite(maskBoundaryFilepath,highlightBorder(bcOutput.energySolution.outputDS));
}

void outputEnergy(const BCOutput& bcOutput,const GrabCutObject& gco, const std::string& outputFolder)
{
  const BCOutput::EnergySolution& solution = bcOutput.energySolution;
  const ModelParameters& modelParameters = bcOutput.bcInput.modelParameters;
  const ImageData& imageData = bcOutput.bcInput.imageData;

  double outputElasticaEnergy,inputElasticaEnergy;

  SCaBOliC::Utils::ISQEvaluation::IICurvatureExtraData extraData(true,modelParameters.radius);
  inputElasticaEnergy = SCaBOliC::Utils::ISQEvaluation::ii(*imageData.inputDS,1.0,&extraData);
  outputElasticaEnergy = SCaBOliC::Utils::ISQEvaluation::ii(solution.outputDS,1.0,&extraData);

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


int main(int argc, char* argv[])
{
  InputReader::InputData inputData = InputReader::readInput(argc,argv);

  GrabCutObject gco = read(inputData.grabcutFile);

  BTools::Utils::Timer::start();


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
                      inputData.initialDilation);

  BCInput bcInput(modelParameters,
                  imageData,
                  inputData.iterations,
                  inputData.showIterations,
                  inputData.showProgress);

  BCOutput bcOutput(bcInput);

  BTools::API::bce(bcOutput,
                   bcInput);


  if(inputData.outputFolder!="")
  {
    boost::filesystem::create_directories(inputData.outputFolder);
    outputImages(bcOutput,gco,inputData.outputFolder);
    outputEnergy(bcOutput,gco,inputData.outputFolder);
  }


}
