
#include <BinOCS/Experiments/ExpInteractive.h>
#include <BinOCS/Experiments/ROISelection.h>
#include <BinOCS/Experiments/ExpROI.h>

namespace BinOCS
{
    namespace Experiments
    {
        std::string projectDir = PROJECT_DIR;
        std::string imageDir = projectDir + "/images";
        std::string outputDir = projectDir + "/output";
    }
}


using namespace BinOCS::Experiments;

void fromROISelection(std::string dataFilePath)
{

    ExpDataInput di = ExpDataInput::read(dataFilePath);

    boost::filesystem::path pFile(di.imgFilePath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("ROI-Selection");
    pOutputFolder.append(pFile.filename().string());


    ExpROI::expInput.maxIterations=3;
    ExpROI::expInput.estimatingBallRadius=3.0;
    ExpROI::expInput.sqTermWeight=1.0;
    ExpROI::expInput.lengthTermWeight=0.0;
    ExpROI::expInput.dataTermWeight=0.5;

    for(int i=0;i<di.vectorOfROI.size();++i)
    {
       ExpROI(pFile.string(),
              di.vectorOfROI.at(i),
              pOutputFolder.string() + "/ROI-" + std::to_string(i) );
    }
}

void interactive(std::string imgFilepath)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("Interactive");
    pOutputFolder.append(pFile.filename().string());


    ExpInteractive::expInput.maxIterations=1;
    ExpInteractive::expInput.estimatingBallRadius=3.0;
    ExpInteractive::expInput.sqTermWeight=1.0;
    ExpInteractive::expInput.lengthTermWeight=1.0;
    ExpInteractive::expInput.dataTermWeight=5.0;


    ExpInteractive(pFile.string(),pOutputFolder.string());
}

void roiSelection(std::string imgFilepath)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder(outputDir);

    pOutputFolder.append("ROI");
    pOutputFolder.append(pFile.filename().string());

    ROISelection(pFile.string(),pOutputFolder.string());
}

int main()
{
    std::string lena = imageDir + "/lena800.jpg";
    std::string lenaROIData = outputDir + "/ROI/lena800.jpg/data.txt";

    //interactive(lena);
    //roiSelection(lena);
    fromROISelection(lenaROIData);

    return 0;
}

