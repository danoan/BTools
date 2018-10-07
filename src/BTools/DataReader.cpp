#include "BTools/DataReader.h"

using namespace BTools;

void DataReader::readRect(SeedSequenceInput& data,std::ifstream& ifs)
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

void DataReader::readMask(SeedSequenceInput& data,std::ifstream& ifs)
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


DataReader::SeedSequenceInput DataReader::read(std::string filepath)
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