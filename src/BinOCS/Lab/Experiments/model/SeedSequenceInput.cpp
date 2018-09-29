#include "BinOCS/Lab/model/input/SeedSequenceInput.h"

using namespace BinOCS::Lab::Model;

void SeedSequenceInput::readRect(SeedSequenceInput& data,std::ifstream& ifs)
{
    int rectCount;
    ifs >> rectCount;

    int x,y,w,h;
    while(rectCount>0)
    {
        ifs >> x;
        ifs >> y;
        ifs >> w;
        ifs >> h;

        data.vectorOfROI.push_back(cv::Rect(x,y,w,h));
        --rectCount;
    }
}

void SeedSequenceInput::writeRect(const SeedSequenceInput& dataToWrite,std::ofstream& ofs)
{
    const std::vector<cv::Rect>& vroi = dataToWrite.vectorOfROI;
    ofs << vroi.size() << std::endl;
    for(auto it=vroi.begin();it!=vroi.end();++it)
    {
        ofs << it->x << " ";
        ofs << it->y << " ";
        ofs << it->width << " ";
        ofs << it->height << " ";
        ofs << std::endl;
    }
}

void SeedSequenceInput::readMask(SeedSequenceInput& data,std::ifstream& ifs)
{
    int numSequences;
    ifs >> numSequences;

    int numPoints;
    int x,y;
    while(numSequences>0)
    {
        ifs >> numPoints;
        std::vector<cv::Point> sequence;
        while(numPoints>0)
        {
            ifs >> x;
            ifs >> y;
            sequence.push_back(cv::Point(x,y));

            --numPoints;
        }

        data.vsp.push_back(sequence);
        --numSequences;
    }
}

void SeedSequenceInput::writeMask(const SeedSequenceInput& dataToWrite,std::ofstream& ofs)
{
    const VectorOfSequenceOfPoints& vsp = dataToWrite.vsp;
    ofs << vsp.size() << std::endl;
    for(auto itV=vsp.begin();itV!=vsp.end();++itV)
    {
        ofs << itV->size() << std::endl;
        for(auto itS=itV->begin();itS!=itV->end();++itS)
        {
            ofs << itS->x << " "
                << itS->y << std::endl;
        }
    }
}

void SeedSequenceInput::getSelector(SelectorOutput &selectorOutput, unsigned int index)
{
    cv::Mat& mask = selectorOutput.sureFrg;

    mask = cv::Mat::zeros(height,width,CV_8UC1);
    const std::vector<cv::Point>& curr = vsp[index];
    for(auto it=curr.begin();it!=curr.end();++it)
    {
        mask.at<unsigned char>(*it) = 1;
    }

    selectorOutput.possibleFrg = vectorOfROI[index];
}



SeedSequenceInput SeedSequenceInput::read(std::string filepath)
{
    SeedSequenceInput data;
    std::ifstream ifs(filepath);

    ifs >> data.imgFilePath;

    ifs >> data.width;
    ifs >> data.height;

    readRect(data,ifs);
    readMask(data,ifs);

    ifs.close();

    return data;
}

void SeedSequenceInput::write(const SeedSequenceInput& dataToWrite,
                             std::string outputFilepath)
{
    std::ofstream ofs(outputFilepath);

    ofs << dataToWrite.imgFilePath << std::endl;
    ofs << dataToWrite.width << " "
        << dataToWrite.height << std::endl;

    writeRect(dataToWrite,ofs);
    writeMask(dataToWrite,ofs);

    ofs.close();
}