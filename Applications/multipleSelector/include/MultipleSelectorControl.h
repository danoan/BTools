#ifndef BTOOLS_MULTIPLESELECTORCONTROL_H
#define BTOOLS_MULTIPLESELECTORCONTROL_H

#include <string>
#include <BinOCS/RegionSelector/SeedSelectorApplication.h>

#include "BTools/model/input/SeedSequenceInput.h"
#include <BTools/DataWriter.h>

namespace BTools
{
    namespace Application
    {
        class MultipleSelectorControl
        {
        public:
            typedef BinOCS::RegionSelector::SeedSelectorApplication SeedSelector;
            typedef SeedSelector::SelectorOutput SelectorOutput;
            typedef BTools::Model::SeedSequenceInput SeedInput;

        public:
            MultipleSelectorControl(std::string imgFilePath,
                                 std::string windowName,
                                 std::string outputFilepath);


        private:
            void includePointsFromGCMask(std::vector<cv::Point>& vp,
                                         cv::Mat gcMask);

        };
    }
}

#endif //BTOOLS_MULTIPLESELECTORCONTROL_H
