#ifndef BTools_ODRPOOL_H
#define BTools_ODRPOOL_H


#include <map>

#include "BTools/core/model/input/ODRConfigInput.h"
#include "SCaBOliC/Core/interface/ODRInterface.h"
#include "SCaBOliC/Core/ODRPixels/ODRPixels.h"

namespace BTools
{
    namespace Core
    {
        class ODRPool
        {
        public:
            typedef SCaBOliC::Core::ODRInterface ODRInterface;
            typedef SCaBOliC::Core::ODRPixels ODRPixels;

        public:
            static ODRInterface& get(const ODRConfigInput& odrConfigInput)
            {
                if( odrPool.find(odrConfigInput) == odrPool.end() )
                {
                    odrPool[odrConfigInput] = createODR(odrConfigInput);
                }
                return *odrPool[odrConfigInput];
            }

        private:

            static ODRInterface* createODR(const ODRConfigInput& odrConfigInput)
            {
                return new ODRPixels(odrConfigInput.radius,
                                     odrConfigInput.gridStep,
                                     odrConfigInput.levels,
                                     odrConfigInput.levelDefinition,
                                     odrConfigInput.neighborhood);
            }


        private:
            static std::unordered_map<ODRConfigInput,ODRInterface*> odrPool;

        };
    }
}
#endif //BTools_ODRPOOL_H

