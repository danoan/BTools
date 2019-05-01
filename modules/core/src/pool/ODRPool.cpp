#include "BTools/core/pool/ODRPool.h"

using namespace BTools::Core;

std::unordered_map<ODRConfigInput,ODRPool::ODRInterface*> ODRPool::odrPool;