#include "GeneralInstance.h"

using namespace BinOCS::Lab::Model;

template<class TInput>
void GeneralInstance<TInput>::write(std::ostream& os,
                                    const std::string& outputFolder)
{
    os << "***GENERAL INPUT***" << std::endl;
    Utils::write(vectorOfInput[0], os);
    os << std::endl;

    std::string imageOutputFilename;
    std::string imageBaseFilename = outputFolder + "/baseImg.jpg";

    if(outputFolder!="-")
        cv::imwrite(imageBaseFilename,vectorOfOutput[0].inputImage);

    std::string (*fnS)(std::string) = [](std::string s){ return Utils::fixedStrLength(20,s); };
    std::string (*fnD)(double) = [](double v){ return Utils::fixedStrLength(20,v); };
    os << fnS(instanceName) << "\t"
       << fnS("Opt.Energy Value") << "\t"
       << fnS("II Elastica") << "\t"
       << fnS("MDCA Elastica") << "\t"
       << fnS("Unlabeled") << std::endl;


    for(int i=0;i<vectorOfOutput.size();++i)
    {
        const OptOutput& currO = vectorOfOutput[i];
        const TInput& currI = vectorOfInput[i];

        os << fnS( currI.bcInput.inputName ) << "\t"
           << fnD( currO.optEnergyValue ) << "\t"
           << fnD(currO.IIElasticaValue) << "\t"
           << fnD(currO.MDCAElasticaValue) << "\t"
           << fnD(currO.unlabeled) << std::endl;

        imageOutputFilename = outputFolder + "/" + currI.bcInput.inputName + "-ROI-" + std::to_string(i) + ".jpg";
        if(outputFolder!="-")
            cv::imwrite(imageOutputFilename,currO.outputImage);
    }
}
