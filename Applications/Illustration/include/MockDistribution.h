#ifndef BINOCS_EXPERIMENTS_MOCKDISTRIBUTION_H
#define BINOCS_EXPERIMENTS_MOCKDISTRIBUTION_H

#include <SCaBOliC/Energy/ISQ/Terms/Data/IProbabilityDistribution.h>
#include <cstdlib>

namespace BTools
{
    namespace Application
    {
        namespace Illustration
        {
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
        }
    }
}

#endif //BINOCS_EXPERIMENTS_MOCKDISTRIBUTION_H
