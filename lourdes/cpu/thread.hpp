#ifndef __LOURDES_CPU_THREAD_HPP
#define __LOURDES_CPU_THREAD_HPP

namespace lourdes { namespace cpu {

class ThreadImpl;

class Thread
{
public:
    Thread();
    virtual ~Thread();

    void start();
    void join();

public:
    virtual void run() = 0;
    
private:
    ThreadImpl* impl;
};

}}

#endif // __LOURDES_CPU_THREAD_HPP
