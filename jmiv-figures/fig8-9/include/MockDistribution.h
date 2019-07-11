#ifndef EXPERIMENTS_MOCKDISTRIBUTION_H
#define EXPERIMENTS_MOCKDISTRIBUTION_H

#include <SCaBOliC/Energy/ISQ/Terms/Data/IProbabilityDistribution.h>
#include <cstdlib>

class MockDistribution:public SCaBOliC::Energy::ISQ::IProbabilityDistribution<double>
{
public:

    MockDistribution()
    {
        srand(time(NULL));
    }

    double operator()(Index row, Index col) const
    {
        return 1.0/( ( rand()%20 )+1.1 );
    }

};


#endif //EXPERIMENTS_MOCKDISTRIBUTION_H
