#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

#include "InputData.h"
#include "UnlabeledRow.h"
#include "countUnlabeled.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        std::cerr << "Usage: " << argv[0] << " IMAGES_FOLDER OUTPUT_FOLDER  METHOD MODE\n";
        exit(1);
    }

    std::string imagesFolder = argv[1];
    std::string outputFolder = argv[2];

    InputData id;
    if(strcmp(argv[3],"simple")==0) id.method = InputData::Simple;
    else id.method = InputData::Probe;

    if(strcmp(argv[4],"concavities")==0) id.mode = InputData::Concavities;
    else id.mode = InputData::Convexities;

    id.radius = std::atoi( argv[5] );


    boost::filesystem::create_directories(outputFolder);

    std::vector<std::vector<UnlabeledRow> > data(id.radius);
    std::ofstream** streams = (std::ofstream**) malloc(sizeof(std::ofstream*)*id.radius);
    for(int i=0;i<id.radius;++i) streams[i] = new std::ofstream(outputFolder + "/level-" + std::to_string(i+1) + ".txt",std::ios::out);


    boost::filesystem::directory_iterator di(imagesFolder);
    boost::filesystem::path currPath;
    while(di!=boost::filesystem::directory_iterator())
    {
        currPath = di->path();
        std::string imageNum = currPath.stem().string();
        while(imageNum[0]=='0' and imageNum.size()>1) imageNum = imageNum.substr(1,imageNum.size()-1);
        if(boost::filesystem::is_regular_file(currPath) && currPath.extension().string()==".pgm")
        {
            std::cout << "Analysis of image: " << imageNum << std::endl;
            for(int i=0;i<id.radius;++i)
            {
                id.levels = i+1;
                CountData cd = countUnlabeled(id,digitalSetFromImage(currPath.string()));

                data[i].push_back( UnlabeledRow(std::atoi(imageNum.c_str()),cd.unlabeledPercentage,cd.pairwisePercentage) );
            }
        }
        ++di;
    }

    for(int i=0;i<id.radius;++i)
    {
        std::sort(data[i].begin(),data[i].end());

        for(auto it=data[i].begin();it!=data[i].end();++it)
        {
            *streams[i] << it->imageNum << "\t"
                        << it->unlabeledPercentage << "\t"
                        << it->pairwiseTermsPercentage << "\n";
        }

        streams[i]->flush();
        streams[i]->close();
        delete streams[i];
    }
}