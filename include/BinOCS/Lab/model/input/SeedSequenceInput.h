#ifndef BINOCS_EXPERIMENTS_MASKSEQUENCEINPUT_H
#define BINOCS_EXPERIMENTS_MASKSEQUENCEINPUT_H

#include <fstream>
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include <BinOCS/Application/RegionSelector/SeedSelectorApplication.h>

namespace BinOCS
{
    namespace Lab
    {
        namespace Model
        {
            class SeedSequenceInput
            {
            public:
                typedef std::vector< std::vector<cv::Point> > VectorOfSequenceOfPoints;
                typedef std::vector<cv::Rect> VectorOfRect;

                typedef BinOCS::Application::SeedSelectorApplication::SelectorOutput SelectorOutput;

            public:
                static SeedSequenceInput read(std::string filepath);
                static void write(const SeedSequenceInput& dataToWrite,
                                  std::string outputFilepath);

                inline unsigned int numSeed(){return vsp.size();}

                void getSelector(SelectorOutput& selectorOutput, unsigned int index);
            private:
                static void readRect(SeedSequenceInput& data,std::ifstream& ifs);
                static void writeRect(const SeedSequenceInput& dataToWrite,std::ofstream& ofs);

                static void readMask(SeedSequenceInput& data,std::ifstream& ifs);
                static void writeMask(const SeedSequenceInput& dataToWrite,std::ofstream& ofs);

            public:
                std::string imgFilePath;
                int width,height;

                VectorOfSequenceOfPoints vsp;
                VectorOfRect vectorOfROI;
            };
        }
    }
}

#endif //BINOCS_EXPERIMENTS_MASKSEQUENCEINPUT_H
