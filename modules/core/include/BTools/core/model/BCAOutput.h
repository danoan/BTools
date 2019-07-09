#ifndef BTools_BCAOUTPUT_H
#define BTools_BCAOUTPUT_H

#include <opencv2/core/mat.hpp>
#include <SCaBOliC/Energy/model/Solution.h>
#include <DIPaCUS/base/Representation.h>

#include "BTools/core/model/input/BCApplicationInput.h"

namespace BTools
{
    namespace Core
    {
        class BCApplicationOutput
        {
        public:
            typedef SCaBOliC::Energy::Solution EnergySolution;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

        public:
            BCApplicationOutput(const BCApplicationInput& bcaInput):bcaInput(bcaInput),
                                                                    imgSeg(bcaInput.imageDataInput.segResult.clone()),
                                                                    energySolution(bcaInput.imageDataInput.inputDomain)
            {}

            BCApplicationOutput& operator=(const BCApplicationOutput& other)
            {
                this->energySolution = other.energySolution;
                this->imgSeg = other.imgSeg;
                this->imgOutput = other.imgOutput;

                return *this;
            }

            BCApplicationOutput(const BCApplicationInput& bcaInput,
                                const EnergySolution& energySolution,
                                const cv::Mat& imgOutput):bcaInput(bcaInput),
                                                          imgSeg(bcaInput.imageDataInput.segResult.clone()),
                                                          energySolution(bcaInput.imageDataInput.inputDomain),
                                                          imgOutput(imgOutput){}
        private:
            const BCApplicationInput& bcaInput;

        public:
            EnergySolution energySolution;
            cv::Mat imgSeg;
            cv::Mat imgOutput;
        };
    }
}

#endif //BTools_BCAOUTPUT_H
