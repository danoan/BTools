#ifndef BTOOLS_UTILS_TIMER_H
#define BTOOLS_UTILS_TIMER_H

#include <boost/date_time.hpp>
#include <ostream>

namespace BTools
{
namespace Utils
{
namespace Timer
{
extern boost::posix_time::ptime startTime;
extern boost::posix_time::ptime endTime;

void start();
void end(std::ostream& os);
}
}
}



#endif //BTOOLS_UTILS_TIMER_H
