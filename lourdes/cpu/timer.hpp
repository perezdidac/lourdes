#ifndef __LOURDES_CPU_TIMER_HPP
#define __LOURDES_CPU_TIMER_HPP

/// \example    examples/cpu/timer.cpp
namespace lourdes { namespace cpu {

class TimerImpl;

/// \brief  Represents an object that measures real time between calls.
class Timer
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    Timer();

    /// \brief  Destroys the object and all the associated resources to it.
    ~Timer();
    
    /// \brief  Restarts the timer using as a reference time the exact time
    /// while this method is called.
    void restart();

    /// \brief  Returns the time, in milliseconds, elapsed between the last
    /// timer restart and the current call to this method.
    /// \return Elapsed time in milliseconds.
    int elapsed();

private:
    Timer(Timer const&);
    Timer& operator=(Timer const&);
    TimerImpl* impl;
};

}}

#endif // __LOURDES_CPU_TIMER_HPP
