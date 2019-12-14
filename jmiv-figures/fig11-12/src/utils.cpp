#include "utils.h"

DGtal::Z2i::DigitalSet digitalSetFromImage(const std::string& imageFilePath)
{
    typedef DIPaCUS::Representation::Image2D Image2D;
    Image2D image = DGtal::GenericReader<Image2D>::import(imageFilePath);
    DGtal::Z2i::DigitalSet dsOut(image.domain());
    DIPaCUS::Representation::imageAsDigitalSet(dsOut,image,1);

    return dsOut;
}