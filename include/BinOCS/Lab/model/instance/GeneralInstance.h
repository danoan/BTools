#ifndef BINOCS_EXPERIMENTS_BCORRECTIONINSTANCE_H
#define BINOCS_EXPERIMENTS_BCORRECTIONINSTANCE_H

#include <vector>
#include <ostream>

#include <BinOCS/Lab/utils.h>
#include <BinOCS/Lab/model/OptOutput.h>
#include <BinOCS/Lab/model/input/ROICorrectionInput.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            template<typename TInput>
            struct GeneralInstance
            {
            public:
                typedef TInput Input;
                typedef OptOutput Output;

            public:
                GeneralInstance(std::string instanceName):instanceName(instanceName){};

                void write(std::ostream& os,
                           const std::string& outputFolder="-");

            public:
                std::vector<TInput> vectorOfInput;
                std::vector<Output> vectorOfOutput;

            private:
                std::string instanceName;
            };


            template<>
            struct GeneralInstance<ROICorrectionInput>
            {
            public:
                typedef ROICorrectionInput Input;
                typedef OptOutput Output;

            public:
                GeneralInstance(std::string instanceName, int numROIPerInput):instanceName(instanceName),
                                                                              numROIPerInput(numROIPerInput){}

            public:
                std::vector<ROICorrectionInput> vectorOfInput;
                std::vector< std::vector<Output> > vectorOfOutput;

                void write(std::ostream& os,
                           const std::string& outputFolder="-")
                {
                    os << "***GENERAL INPUT***" << std::endl;
                    Utils::write(vectorOfInput[0],os);
                    os << std::endl;

                    std::string (*fnS)(std::string) = [](std::string s){ return Utils::fixedStrLength(20,s); };
                    std::string (*fnD)(double) = [](double v){ return Utils::fixedStrLength(20,v); };

                    std::string imageOutputFilename;
                    std::string imageBaseFilename = outputFolder + "/baseImg.jpg";

                    if(outputFolder!="-")
                        cv::imwrite(imageBaseFilename,vectorOfOutput[0][0].inputImage);

                    for(int i=0;i<numROIPerInput;++i)
                    {
                        os << fnS(instanceName + "-ROI-" + std::to_string(i+1) ) << "\t"
                           << fnS("Opt.Energy Value") << "\t"
                           << fnS("II Elastica") << "\t"
                           << fnS("MDCA Elastica") << "\t"
                           << fnS("Unlabeled") << std::endl;

                        for(int j=0;j<vectorOfInput.size();++j)
                        {
                            const OptOutput& currO = vectorOfOutput[j][i];
                            const ROICorrectionInput& currI = vectorOfInput[j];

                            os << fnS(currI.bcInput.inputName) << "\t"
                               << fnD(currO.optEnergyValue ) << "\t"
                               << fnD(currO.IIElasticaValue) << "\t"
                               << fnD(currO.MDCAElasticaValue) << "\t"
                               << fnD(currO.unlabeled) << std::endl;

                            imageOutputFilename = outputFolder + "/" + currI.bcInput.inputName + "-ROI-" + std::to_string(i) + ".jpg";
                            if(outputFolder!="-")
                                cv::imwrite(imageOutputFilename,currO.outputImage);
                        }

                        os << std::endl;
                    }
                }


            private:
                std::string instanceName;
                int numROIPerInput;
            };

        }
    }
}

#include "GeneralInstance.hpp"

#endif //BINOCS_EXPERIMENTS_BCORRECTIONINSTANCE_H
