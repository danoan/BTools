#include "BinOCS/Lab/Experiments/ExpDataset.h"

using namespace BinOCS::Lab::Experiments;


ExpDataset::ExpDataset(std::string datasetPath,bool ROISelection)
{
    assert(boost::filesystem::is_directory(datasetPath));
    executeROICorrection(datasetPath);
}


void ExpDataset::executeInstance(OptOutput& output,
                                 const BCorrectionInput& bcInput,
                                 const SelectorOutput& selectorOutput,
                                 const std::string& imgFilePath)
{
    GCApplication::GrabCutResult result;
    cv::Mat baseImage = cv::imread(imgFilePath,CV_LOAD_IMAGE_COLOR);

    GCApplication::executeFromSeed(result,selectorOutput);

    CVMatDistribution fgDistr(baseImage,
                              result.fgModel);

    CVMatDistribution bgDistr(baseImage,
                              result.bgModel);

    BCConfigData configData(bcInput.estimatingBallRadius,
                            fgDistr,
                            bgDistr,
                            bcInput.dataTermWeight,
                            bcInput.sqTermWeight,
                            bcInput.lengthTermWeight);


    BCSolution solution = BCApplication::solutionModel(result.foreground);
    BCApplication bca(solution,
                      bcInput.maxIterations,
                      result.foreground,
                      configData);


    DisplayData dd = bca.displayResult(solution,
                                       result.baseImage,
                                       result.foreground);




    output.optEnergyValue = solution.energyValue;
    output.unlabeled = solution.unlabeled;
    output.inputImage = result.foreground;
    output.outputImage = dd.imgOutput;


    SCaBOliC::Utils::MDCAISQEvaluation(output.MDCAElasticaValue,
                                       solution.outputDS);


    /*    SCaBOliC::Utils::IIISQEvaluation(output.IIElasticaValue,
                                         solution.outputDS); */

    output.IIElasticaValue =-1;


}

void ExpDataset::executeROICorrection(std::string datasetPathStr)
{
    boost::filesystem::path datasetPath(datasetPathStr);
    boost::filesystem::directory_iterator di(datasetPath);
    while(di!=boost::filesystem::directory_iterator())
    {
        if(di->path().extension()==".txt")
        {

            std::string dataPath = di->path().string();
            std::string imageName = di->path().stem().string();
            SeedSequenceInput roiInput = SeedSequenceInput::read(dataPath);

            boost::filesystem::path outputPath(datasetPath);
            outputPath.append(imageName);
            boost::filesystem::create_directories(outputPath);


            int totalSeed = roiInput.numSeed();
            MyInstance instance(
                    imageName, totalSeed);

            CurvatureProfile curvProfile(InstanceProfile::Curvature);
            BCorrectionInput bcInput("noname");

            while (curvProfile.fillInstance(bcInput)) {
                SeedCorrectionInput seedcInput(bcInput.inputName);
                seedcInput.seedInput = roiInput;
                seedcInput.bcInput = bcInput;

                SelectorOutput selectorOutput;
                std::vector<OptOutput> ROIOutput;
                for (int i = 0; i < totalSeed; ++i) {
                    OptOutput output;
                    roiInput.getSelector(selectorOutput,i);

                    executeInstance(output,
                                    bcInput,
                                    selectorOutput,
                                    roiInput.imgFilePath);

                    ROIOutput.push_back(output);
                }

                instance.vectorOfInput.push_back(seedcInput);
                instance.vectorOfOutput.push_back(ROIOutput);
            }

            instance.write(std::cout,
                           outputPath.string());

            break;
        }

        di++;
    }


}