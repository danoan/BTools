#include <BinOCS/API.h>
#include "../include/InteractiveControl.h"

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

    const Solution& solution = bcaOutput.energySolution;



    double outputElasticaEnergy,inputElasticaEnergy;
    SCaBOliC::Utils::MDCAISQEvaluation(outputElasticaEnergy,
                                       solution.outputDS);

    DigitalSet baseImageDS(solution.outputDS.domain());
    DIPaCUS::Representation::ImageAsDigitalSet(baseImageDS,imageFilePath);
    SCaBOliC::Utils::MDCAISQEvaluation(inputElasticaEnergy,baseImageDS);

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


