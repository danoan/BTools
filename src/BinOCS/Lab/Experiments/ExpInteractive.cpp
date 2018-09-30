#include "BinOCS/Lab/Experiments/ExpInteractive.h"

using namespace BinOCS::Lab::Experiments;

ExpInteractive::ExpInteractive(const Model::GrabCorrectionInput& expInput,
                               std::string outputFolder)
{
    boost::filesystem::create_directories(outputFolder);


    GrabCutResult result;
    GCApplication ga(expInput.imagePath,result);

    cv::destroyWindow(ga.windowName);

    CVMatDistribution fgDistr(result.baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(result.baseImage,
                              result.bgModel);


    BCConfigData configData(expInput.bcInput.estimatingBallRadius,
                            fgDistr,
                            bgDistr,
                            expInput.bcInput.dataTermWeight,
                            expInput.bcInput.sqTermWeight,
                            expInput.bcInput.lengthTermWeight);


    BCSolution solution = BCApplication::solutionModel(result.foreground);
    BCApplication bca(solution,
                      expInput.bcInput.maxIterations,
                      result.foreground,
                      configData);

    DisplayData dd = bca.displayResult(solution,
                                       result.baseImage,
                                       result.foreground);

    double outputElasticaEnergy,inputElasticaEnergy;
    SCaBOliC::Utils::MDCAISQEvaluation(outputElasticaEnergy,
                                       solution.outputDS);

    DigitalSet baseImageDS(solution.outputDS.domain());
    DIPaCUS::Representation::ImageAsDigitalSet(baseImageDS,expInput.imagePath);
    SCaBOliC::Utils::MDCAISQEvaluation(inputElasticaEnergy,baseImageDS);

    std::ofstream ofs(outputFolder + "/energy.txt");
    ofs << "GrabCut Segmentation Elastica Energy: " << inputElasticaEnergy << "\n"
        << "Boundary Correction Elastica Energy: " << outputElasticaEnergy << std::endl;
    ofs.close();

    cv::imwrite(outputFolder + "/gc-seg.jpg",result.foreground);
    cv::imwrite(outputFolder +"/corrected-seg.jpg",dd.imgOutput);

    cv::destroyAllWindows();

    cv::Rect r = Utils::computeBoundingBox(result.foreground);

    Utils::showManyImages("Boundary Correction",2,result.foreground(r),dd.imgOutput(r));

}


