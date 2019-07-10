#ifndef EXPERIMENTS_UTILS_H
#define EXPERIMENTS_UTILS_H

#include <string>
#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/base/Representation.h>

DGtal::Z2i::DigitalSet digitalSetFromImage(const std::string& imageFilePath);

#endif //EXPERIMENTS_UTILS_H
