#include "BinOCS/Lab/Experiments/ExpDataset.h"

using namespace BinOCS::Lab::Experiments;


ExpDataset::ExpDataset(std::string datasetPath,bool ROISelection)
{
    assert(boost::filesystem::is_directory(datasetPath));

    if(ROISelection)
        datasetROISelection(datasetPath);
    else
        executeROICorrection(datasetPath);
}

void ExpDataset::selectROI(std::string imgFilepath,
               std::string outputDir,
               std::string filename)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder(outputDir);

    Experiments::ExpROISelection(pFile.string(),
                                 pOutputFolder.string(),
                                 filename);
}

void ExpDataset::datasetROISelection(std::string datasetPathStr)
{
    boost::filesystem::path datasetPath(datasetPathStr);
    boost::filesystem::directory_iterator di(datasetPath);
    while(di!=boost::filesystem::directory_iterator())
    {
        if(boost::filesystem::is_regular_file(di->path()) &&
           di->path().extension()!=".txt")
        {

            std::string imagePath = di->path().string();
            selectROI(imagePath,
                      datasetPath.string(),
                      di->path().stem().string() + ".txt");
        }

        ++di;
    }
};

void ExpDataset::executeInstance(OptOutput& output,
                                 const BCorrectionInput& bcInput,
                                 const std::string& imgFilePath,
                                 const cv::Rect& ROI)
{
    GCApplication::GrabCutResult result;
    cv::Mat baseImage = cv::imread(imgFilePath,CV_LOAD_IMAGE_COLOR);
    GCApplication::executeFromROI(result,baseImage,ROI);

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



    cv::Rect extendedROI = result.ROI;
    extendedROI.x-=5;
    extendedROI.y-=5;
    extendedROI.width+=5;
    extendedROI.height+=5;


    output.optEnergyValue = solution.energyValue;
    output.unlabeled = solution.unlabeled;
    output.inputImage = result.foreground(extendedROI);
    output.outputImage = dd.imgOutput(extendedROI);


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
            ROISequenceInput roiInput = ROISequenceInput::read(dataPath);

            boost::filesystem::path outputPath(datasetPath);
            outputPath.append(imageName);
            boost::filesystem::create_directories(outputPath);


            int totalROI = roiInput.vectorOfROI.size();
            GeneralInstance<ROICorrectionInput> instance(
                    imageName, totalROI);

            CurvatureProfile curvProfile(InstanceProfile::Curvature);
            BCorrectionInput bcInput("noname");
            while (curvProfile.fillInstance(bcInput)) {
                ROICorrectionInput roicInput(bcInput.inputName);
                roicInput.roiInput = roiInput;
                roicInput.bcInput = bcInput;

                std::vector<OptOutput> ROIOutput;
                for (int i = 0; i < totalROI; ++i) {
                    OptOutput output;
                    executeInstance(output,
                                    bcInput,
                                    roiInput.imgFilePath,
                                    roiInput.vectorOfROI[i]);

                    ROIOutput.push_back(output);
                }

                instance.vectorOfInput.push_back(roicInput);
                instance.vectorOfOutput.push_back(ROIOutput);
            }

            instance.write(std::cout,
                           outputPath.string());

            break;
        }

        di++;
    }


}