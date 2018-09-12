#include <fstream>
#include "BinOCS/Experiments/model/ExpDataInput.h"

using namespace BinOCS::Experiments;

ExpDataInput ExpDataInput::read(std::string filepath)
{
    ExpDataInput data;
    std::ifstream ifs(filepath);

    ifs >> data.imgFilePath;

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

    ifs.close();
}

void ExpDataInput::write(const ExpDataInput& dataToWrite,
                         std::string outputFilepath)
{
    std::ofstream ofs(outputFilepath);

    ofs << dataToWrite.imgFilePath << std::endl;

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
    ofs.close();
}