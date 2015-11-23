#ifndef __LOURDES_CPU_TIMER_HPP
#define __LOURDES_CPU_TIMER_HPP

namespace lourdes { namespace cpu {

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

}}

#endif // __LOURDES_CPU_TIMER_HPP
