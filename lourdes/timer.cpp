#include "timer.hpp"

// Boost includes
#include <boost/chrono.hpp>

namespace lourdes {

class TimerImpl
{
public:
    boost::chrono::steady_clock::time_point last;
};

Timer::Timer()
{
    impl = new TimerImpl;
    restart();
}

Timer::~Timer()
{
    delete impl;
}

void Timer::restart()
{
    impl->last = boost::chrono::steady_clock::now();
}

int Timer::elapsed()
{
    return (int)boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::steady_clock::now() - impl->last).count();
}

}
