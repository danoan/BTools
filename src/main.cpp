
#include <BinOCS/Experiments/ExpInteractive.h>
#include <BinOCS/Experiments/ROISelection.h>

using namespace BinOCS::Experiments;

void interactive(std::string imgFilepath)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder("../output");

    pOutputFolder.append("Interactive");
    pOutputFolder.append(pFile.filename().string());


    ExpInteractive::expInput.maxIterations=1;
    ExpInteractive::expInput.estimatingBallRadius=3.0;
    ExpInteractive::expInput.sqTermWeight=1.0;
    ExpInteractive::expInput.dataTermWeight=-5.0;

    ExpInteractive(pFile.string(),pOutputFolder.string());
}

void roiSelection(std::string imgFilepath)
{
    boost::filesystem::path pFile(imgFilepath);
    boost::filesystem::path pOutputFolder("../output");

    pOutputFolder.append("ROI");
    pOutputFolder.append(pFile.filename().string());

    ROISelection(pFile.string(),pOutputFolder.string());
}

int main()
{
    std::string lena = "../images/lena800.jpg";

    interactive(lena);
    //roiSelection(lena);

    return 0;
}

