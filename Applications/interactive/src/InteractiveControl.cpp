#include <BinOCS/API.h>
#include "InteractiveControl.h"

using namespace BTools::Application;

InteractiveControl::InteractiveControl(const BCFlowInput& bcFlowInput,
                                       const std::string& imageFilePath,
                                       std::string outputFolder)
{
    boost::filesystem::create_directories(outputFolder);

    typedef BinOCS::API::SegCorrect::BCAOutput BCAOutput;
    BCAOutput bcaOutput = BinOCS::API::segCorrect(imageFilePath,
                                                  bcFlowInput.bcInput,
                                                  bcFlowInput.maxIterations);

    const BCSolution& solution = bcaOutput.energySolution;



    double outputElasticaEnergy,inputElasticaEnergy;
    SCaBOliC::Utils::ISQEvaluation(outputElasticaEnergy,
                                   solution.outputDS,
                                   SCaBOliC::Utils::ISQEvaluation::MDCA);

    DigitalSet baseImageDS(solution.outputDS.domain());
    DIPaCUS::Representation::imageAsDigitalSet(baseImageDS,imageFilePath);
    SCaBOliC::Utils::ISQEvaluation(inputElasticaEnergy,baseImageDS,
                                   SCaBOliC::Utils::ISQEvaluation::MDCA);

    std::ofstream ofs(outputFolder + "/energy.txt");
    ofs << "GrabCut Segmentation Elastica Energy: " << inputElasticaEnergy << "\n"
        << "Boundary Correction Elastica Energy: " << outputElasticaEnergy << std::endl;
    ofs.close();

    cv::imwrite(outputFolder + "/gc-seg.jpg",bcaOutput.imgSeg);
    cv::imwrite(outputFolder +"/corrected-seg.jpg",bcaOutput.imgOutput);

    cv::destroyAllWindows();

    cv::Rect r = BTools::Utils::computeBoundingBox(bcaOutput.imgSeg);

    BTools::Utils::showManyImages("Boundary Correction",2,bcaOutput.imgSeg(r),bcaOutput.imgOutput(r));

}


