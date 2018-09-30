#include "BinOCS/Lab/Experiments/ExpDataset.h"

using namespace BinOCS::Lab::Experiments;


ExpDataset::ExpDataset(std::string datasetPath,
                       std::string outputFolder)
{
    assert(boost::filesystem::is_directory(datasetPath));
    executeROICorrection(datasetPath,
                         outputFolder);
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

void ExpDataset::executeROICorrection(std::string datasetPathStr,
                                      std::string outputFolder)
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

            boost::filesystem::path outputPath(outputFolder);
            outputPath.append(imageName);
            boost::filesystem::create_directories(outputPath);


            int totalSeed = roiInput.numSeed();
            MyInstance instance(
                    imageName, totalSeed);

            DataTermProfile dtProfile;
            BCorrectionInput bcInput("noname");

            SelectorOutput selectorOutput;
            selectorOutput.baseImage = cv::imread(roiInput.imgFilePath,CV_LOAD_IMAGE_COLOR);
            while (dtProfile.fillInstance(bcInput)) {
                SeedCorrectionInput seedcInput(bcInput.inputName);
                seedcInput.seedInput = roiInput;
                seedcInput.bcInput = bcInput;

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

            std::ofstream ofs( (outputPath.string() + "/values.txt").c_str() );

            instance.write(ofs,
                           outputPath.string());

            ofs.close();
        }

        di++;
    }


}