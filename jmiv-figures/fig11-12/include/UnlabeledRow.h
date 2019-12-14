#ifndef EXPERIMENTS_UNLABELEDROW_H
#define EXPERIMENTS_UNLABELEDROW_H

struct UnlabeledRow
{
    UnlabeledRow(int imageNum,
                 double unlabeledPercentage,
                 double pairwiseTermsPercentage) : imageNum(imageNum),
                                                   unlabeledPercentage(unlabeledPercentage),
                                                   pairwiseTermsPercentage(pairwiseTermsPercentage){}

    int imageNum;
    double pairwiseTermsPercentage;
    double unlabeledPercentage;

    bool operator<(const UnlabeledRow& other) const
    {
        return this->imageNum < other.imageNum;
    }
};

#endif //EXPERIMENTS_UNLABELEDROW_H
