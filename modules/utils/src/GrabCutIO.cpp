#include "BTools/utils/model/GrabCutObject.h"

using namespace BTools::Utils;

void GrabCutIO::write(const GrabCutObject& gco, const std::string& outputPath)
{
    boost::filesystem::path p(outputPath);
    boost::filesystem::create_directories(p.remove_filename());

    cv::FileStorage gcObjectFile(outputPath,cv::FileStorage::WRITE);
    gcObjectFile << "grabCutMask" << gco.grabCutMask;
    gcObjectFile << "segMask" << gco.segMask;
    gcObjectFile << "inputImage" << gco.inputImage;
    gcObjectFile << "seeds" << gco.seeds;

    gcObjectFile.release();
}

GrabCutIO::GrabCutObject GrabCutIO::read(const std::string &grabCutObjectFile)
{
    GrabCutIO::GrabCutObject gco;

    cv::FileStorage grabcutObjectFile(grabCutObjectFile,cv::FileStorage::READ);
    grabcutObjectFile["grabCutMask"] >> gco.grabCutMask;
    grabcutObjectFile["segMask"] >> gco.segMask;
    grabcutObjectFile["inputImage"] >> gco.inputImage;
    grabcutObjectFile["seeds"] >> gco.seeds;

    return gco;
}