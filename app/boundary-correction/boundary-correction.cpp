#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <boost/filesystem.hpp>

#include <SCaBOliC/Utils/Utils.h>

#include "BTools/core/model/input/ImageDataInput.h"
#include "BTools/core/model/input/BCFlowInput.h"
#include "BTools/core/model/input/BCApplicationInput.h"
#include "BTools/core/model/BCAOutput.h"
#include "BTools/core/model/input/ODRConfigInput.h"
#include "BTools/core/model/input/BCConfigInput.h"
#include "BTools/core/model/CVMatDistribution.h"
#include "BTools/core/BCApplication.h"

#include "BTools/utils/imgUtils.h"
#include "BTools/utils/model/GrabCutObject.h"

#include "InputReader.h"


using namespace BTools::Core;
using namespace DGtal::Z2i;

using namespace BoundaryCorrection;
using namespace BTools::Utils::GrabCutIO;

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


BCApplicationOutput boundaryCorrection(const InputReader::InputData& inputData, GrabCutObject& gco)
{
    typedef BTools::Core::BCFlowInput BCFlowInput;
    int levels = 1;
    bool optInApplicationRegion=true;
    bool repeatedImprovement = false;

    BCConfigInput bcConfigInput(inputData.radius,
                                inputData.dtWeight,
                                inputData.sqWeight,
                                inputData.lgWeight,
                                inputData.excludeOptPointsFromAreaComputation,
                                inputData.initialDilation,
                                inputData.optMethod);

    ODRConfigInput odrConfigInput(inputData.radius, 1.0,
            levels,
            ODRConfigInput::LevelDefinition::LD_FartherFromCenter,
            ODRConfigInput::NeighborhoodType::FourNeighborhood,
            optInApplicationRegion);


    cv::Mat segResultImg = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
    gco.inputImage.copyTo(segResultImg,gco.segMask);

    cv::Mat fgModel,bgModel;
    GMM fgGMM(fgModel),bgGMM(bgModel);
    initGMMs(gco.inputImage,gco.grabCutMask,bgGMM,fgGMM);

    CVMatDistribution fgDistr(gco.inputImage,fgGMM);
    CVMatDistribution bgDistr(gco.inputImage,bgGMM);

    ImageDataInput imageDataInput(fgDistr,bgDistr,gco.inputImage,segResultImg,inputData.initialDilation);

    BCApplicationInput bcaInput(bcConfigInput,
                                imageDataInput,
                                odrConfigInput,
                                BCFlowInput::FlowProfile::DoubleStep,
                                inputData.showProgress);

    BCApplicationOutput bcaOutput(bcaInput);
    BCApplication bca(bcaOutput,
                      bcaInput,
                      inputData.iterations,
                      inputData.showIterations);

    return bcaOutput;
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

void outputImages(const BCApplicationOutput& bcaOutput, const GrabCutObject& gco, const std::string& outputFolder)
{
    const BCApplicationOutput::EnergySolution& solution = bcaOutput.energySolution;

    std::string graphCutSegFilepath = outputFolder + "/gc-seg.png";
    std::string correctedSegFilepath = outputFolder +"/corrected-seg.png";
    std::string maskBoundaryFilepath = outputFolder +"/mask-boundary.png";


    cv::Mat gcSegImg = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
    BTools::Utils::setHighlightMask(gcSegImg,gco.inputImage,gco.segMask);


    cv::imwrite(graphCutSegFilepath,gcSegImg);
    cv::imwrite(correctedSegFilepath,bcaOutput.imgOutput);
    cv::imwrite(maskBoundaryFilepath,highlightBorder(bcaOutput.energySolution.outputDS));
}

void outputEnergy(const BCApplicationOutput& bcaOutput,const GrabCutObject& gco, const std::string& outputFolder)
{
    const BCApplicationOutput::EnergySolution& solution = bcaOutput.energySolution;

    double outputElasticaEnergy,inputElasticaEnergy;
    SCaBOliC::Utils::ISQEvaluation(outputElasticaEnergy,
                                   solution.outputDS,SCaBOliC::Utils::ISQEvaluation::MDCA);

    cv::Mat gcSegImage = cv::Mat::zeros(gco.inputImage.size(),gco.inputImage.type());
    gco.inputImage.copyTo(gcSegImage ,gco.segMask);

    DGtal::Z2i::Domain baseImageDomain( Point(0,0),
                                        Point(gcSegImage.cols,gcSegImage.rows) );
    DigitalSet baseImageDS( baseImageDomain );

    cv::Mat grayImage(gcSegImage.size(),CV_8UC1);
    cv::cvtColor(gcSegImage,grayImage,cv::ColorConversionCodes::COLOR_BGR2GRAY);

    DIPaCUS::Representation::CVMatToDigitalSet(baseImageDS,grayImage);
    SCaBOliC::Utils::ISQEvaluation(inputElasticaEnergy,
                                   baseImageDS,SCaBOliC::Utils::ISQEvaluation::MDCA);

    std::ofstream ofs(outputFolder + "/energy.txt");
    ofs << "GrabCut Segmentation Elastica Energy: " << inputElasticaEnergy << "\n"
        << "Boundary Correction Elastica Energy: " << outputElasticaEnergy << std::endl;
    ofs.close();
}


int main(int argc, char* argv[])
{
    InputReader::InputData inputData = InputReader::readInput(argc,argv);

    GrabCutObject gco = read(inputData.grabcutFile);

    BCApplicationOutput bcaOutput = boundaryCorrection(inputData,gco);

    if(inputData.outputFolder!="")
    {
        boost::filesystem::create_directories(inputData.outputFolder);
        outputImages(bcaOutput,gco,inputData.outputFolder);
        outputEnergy(bcaOutput,gco,inputData.outputFolder);
    }


}
