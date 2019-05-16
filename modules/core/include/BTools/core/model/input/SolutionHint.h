#ifndef BTOOLS_SOLUTIONHINT_H
#define BTOOLS_SOLUTIONHINT_H

#include <DGtal/helpers/StdDefs.h>

namespace BTools
{
    namespace Core
    {
        class SolutionHint
        {
        public:
            typedef DGtal::Z2i::DigitalSet DigitalSet;

        private:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;

            static Domain mockDomain(){ return Domain(Point(0,0),Point(1,1)); }
        public:
            SolutionHint():ones(mockDomain()),zeros(mockDomain()){}
            SolutionHint(const DigitalSet& ones, const DigitalSet& zeros):ones(ones),zeros(zeros){}

            const DigitalSet ones;
            const DigitalSet zeros;

            static SolutionHint emptySHint;
        };


    }
}

#endif //BTOOLS_SOLUTIONHINT_H
