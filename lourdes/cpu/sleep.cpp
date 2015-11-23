#include "sleep.hpp"

#include <boost/thread.hpp>

namespace lourdes { namespace cpu {

void sleep(int milliseconds)
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(milliseconds));
}

}}
