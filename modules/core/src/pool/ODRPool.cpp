#include "BinOCS/core/pool/ODRPool.h"

using namespace BinOCS::Core;

std::unordered_map<ODRConfigInput,ODRPool::ODRInterface*> ODRPool::odrPool;