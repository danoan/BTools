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
                                                  bcFlowInput.flowConfigInput,
                                                  bcFlowInput.maxIterations);

    const Solution& solution = bcaOutput.energySolution;

    std::string graphCutSegFilepath = outputFolder + "/gc-seg.jpg";
    std::string correctedSegFilepath = outputFolder +"/corrected-seg.jpg";

    cv::imwrite(graphCutSegFilepath,bcaOutput.imgSeg);
    cv::imwrite(correctedSegFilepath,bcaOutput.imgOutput);

    double outputElasticaEnergy,inputElasticaEnergy;
    SCaBOliC::Utils::MDCAISQEvaluation(outputElasticaEnergy,
                                       solution.outputDS);

    DGtal::Z2i::Domain baseImageDomain( Point(0,0),Point(bcaOutput.imgSeg.cols,bcaOutput.imgSeg.rows) );
    DigitalSet baseImageDS( baseImageDomain );

    DIPaCUS::Representation::imageAsDigitalSet(baseImageDS,graphCutSegFilepath);
    SCaBOliC::Utils::MDCAISQEvaluation(inputElasticaEnergy,baseImageDS);

    std::ofstream ofs(outputFolder + "/energy.txt");
    ofs << "GrabCut Segmentation Elastica Energy: " << inputElasticaEnergy << "\n"
        << "Boundary Correction Elastica Energy: " << outputElasticaEnergy << std::endl;
    ofs.close();

    cv::destroyAllWindows();

    cv::Rect r = BTools::Utils::computeBoundingBox(bcaOutput.imgSeg);

    BTools::Utils::showManyImages("Boundary Correction",2,bcaOutput.imgSeg(r),bcaOutput.imgOutput(r));

}


