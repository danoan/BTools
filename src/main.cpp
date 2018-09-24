
#include <BinOCS/Lab/Experiments/ExpInteractive.h>
#include <BinOCS/Lab/Experiments/ExpROISelection.h>
#include <BinOCS/Lab/Experiments/ExpROI.h>
#include <BinOCS/Lab/Experiments/ExpDataset.h>

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
    Model::ROICorrectionInput rci("Standard Input");

    rci.bcInput.maxIterations=3;
    rci.bcInput.estimatingBallRadius=3.0;
    rci.bcInput.sqTermWeight=1.0;
    rci.bcInput.lengthTermWeight=0.0;
    rci.bcInput.dataTermWeight=0.5;

    rci.roiInput = Model::ROISequenceInput::read(dataFilePath);


    boost::filesystem::path pFile(rci.roiInput.imgFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("ROI-Selection");
    pOutputFolder.append(pFile.filename().string());

    for(int i=0;i<rci.roiInput.vectorOfROI.size();++i)
    {
       ExpROI(rci,
              pOutputFolder.string() + "/ROI-" + std::to_string(i) );
    }
}

void interactive(std::string imgFilepath)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("Interactive");
    pOutputFolder.append(pFile.filename().string());

    Model::GrabCorrectionInput gci("Standard Input");

    gci.bcInput.maxIterations=1;
    gci.bcInput.estimatingBallRadius=3.0;
    gci.bcInput.sqTermWeight=1.0;
    gci.bcInput.lengthTermWeight=1.0;
    gci.bcInput.dataTermWeight=5.0;
    gci.imagePath = pFile.string();

    ExpInteractive(gci,pOutputFolder.string());
}

void roiSelection(std::string imgFilepath)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("ROI");
    pOutputFolder.append(pFile.filename().string());

    ExpROISelection(pFile.string(),pOutputFolder.string());
}



int main()
{
    std::string lena = imageDir + "/lena800.jpg";
    std::string lenaROIData = outputDir + "/ROI/lena800.jpg/data.txt";

    //interactive(lena);
    //roiSelection(lena);
    //fromROISelection(lenaROIData);

    ExpDataset(imageDir+"/ds1",false);

    return 0;
}

