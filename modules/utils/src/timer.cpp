#include "BTools/utils/timer.h"

namespace BTools
{
    namespace Utils
    {
        namespace Timer
        {
            boost::posix_time::ptime startTime;
            boost::posix_time::ptime endTime;

            void start()
            {
                startTime = boost::posix_time::microsec_clock::local_time();
            }

            void end(std::ostream& os)
            {
                endTime = boost::posix_time::microsec_clock::local_time();

                boost::posix_time::time_duration diff = endTime - startTime;
                os << diff.total_seconds() << "s " << diff.total_milliseconds() << "ms " << diff.total_microseconds() << "us \n";
            }
        }
    }
}