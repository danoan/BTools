#include <BinOCS/Application/GrabCut/GrabCutApplication.h>

#include <BinOCS/Lab/Experiments/ExpInteractive.h>
#include <BinOCS/Lab/Experiments/ExpFromSeed.h>
#include <BinOCS/Lab/Experiments/ExpDataset.h>

#include <BinOCS/Lab/helpers/MultipleMaskSelector.h>


namespace BinOCS
{
    namespace Lab
    {
        std::string projectDir = PROJECT_DIR;
        std::string imageDir = projectDir + "/images";
        std::string outputDir = projectDir + "/output";
    }
}


using namespace BinOCS::Lab;
using namespace BinOCS::Lab::Experiments;


void fromROISelection(std::string dataFilePath)
{
    typedef BinOCS::Application::GrabCutApplication GCApplication;
    typedef Model::SeedCorrectionInput SeedCorrectionInput;

    SeedCorrectionInput rci("Standard Input");

    rci.bcInput.maxIterations=3;
    rci.bcInput.estimatingBallRadius=3.0;
    rci.bcInput.sqTermWeight=1.0;
    rci.bcInput.lengthTermWeight=0.5;
    rci.bcInput.dataTermWeight=2.5;

    rci.seedInput = SeedCorrectionInput::SeedInput::read(dataFilePath);


    boost::filesystem::path pFile(rci.seedInput.imgFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("From-Seed-Selection");
    pOutputFolder.append(pFile.filename().string());

    ExpFromSeed::SelectorOutput selectorOutput;
    selectorOutput.baseImage = cv::imread(rci.seedInput.imgFilePath,CV_LOAD_IMAGE_COLOR);
    for(int i=0;i<rci.seedInput.numSeed();++i)
    {
        rci.seedInput.getSelector(selectorOutput,i);
        ExpFromSeed(rci.seedInput.imgFilePath,
                    rci.bcInput,
                    selectorOutput,
                    pOutputFolder.string() + "/ROI-" + std::to_string(i) );
    }
}

void interactive(std::string imgFilepath)
{
    typedef BinOCS::Application::GrabCutApplication GCApplication;

    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("Interactive");
    pOutputFolder.append(pFile.filename().string());

    Model::GrabCorrectionInput gci("Standard Input");

    gci.bcInput.maxIterations=5;
    gci.bcInput.estimatingBallRadius=3.0;
    gci.bcInput.sqTermWeight=1.0;
    gci.bcInput.lengthTermWeight=0.1;
    gci.bcInput.dataTermWeight=1.0;
    gci.imagePath = pFile.string();

    ExpInteractive(gci,pOutputFolder.string());
}

namespace BinOCS
{
    namespace Lab
    {
        struct InputData
        {
            InputData(std::string imagePath, std::string dataPath):imagePath(imagePath),
                                                                   dataPath(dataPath){};
            std::string imagePath;
            std::string dataPath;
        };

        namespace InputCollection
        {
            InputData COW2(imageDir + "/ds1/cow2.jpg",
                           outputDir + "/seedData/cow2.txt");

            InputData BUTTERFLY1(imageDir + "/ds1/butterfly1.jpg",
                                 outputDir + "/seedData/butterfly1.txt");

            InputData BUTTERFLY2(imageDir + "/ds1/butterfly2.jpg",
                                 outputDir + "/seedData/butterfly2.txt");

        }
    }
}

void multipleSelection(std::string datasetPathStr)
{
    boost::filesystem::path datasetPath(datasetPathStr);
    boost::filesystem::directory_iterator di(datasetPath);

    std::string outputFilepath;
    std::string windowName = "Mask Selector";
    while(di!=boost::filesystem::directory_iterator())
    {
        if(di->path().extension()==".jpg")
        {
            outputFilepath = outputDir + "/seedData/" + di->path().stem().string() + ".txt";
            Helpers::MultipleMaskSelector MMS(di->path().string(),
                                                  windowName,
                                                  outputFilepath);
            cv::destroyWindow(windowName);
        }
        ++di;
    }
}


int main()
{
    typedef BinOCS::Application::GrabCutApplication GCApplication;
    typedef Model::SeedSequenceInput SeedInput;


    InputData input = InputCollection::COW2;

    //multipleSelection(imageDir + "/ds1");
//    Helpers::MultipleMaskSelector MMS(input.imagePath,
//                                      "Mask Selector",
//                                      input.dataPath);


    interactive(input.imagePath);
    //fromROISelection(input.dataPath);

    //ExpDataset(imageDir+"/ds1",outputDir + "/Dataset-3it");

    return 0;
}

