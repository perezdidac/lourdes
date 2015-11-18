#ifndef __LOURDES_TIMER_HPP
#define __LOURDES_TIMER_HPP

namespace lourdes {

class TimerImpl;

class Timer
{
public:
    Timer();
    ~Timer();
    
    void restart();
    int elapsed();

private:
    TimerImpl* impl;
};

}

#endif // __LOURDES_TIMER_HPP
