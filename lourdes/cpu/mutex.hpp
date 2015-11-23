#ifndef __LOURDES_CPU_MUTEX_HPP
#define __LOURDES_CPU_MUTEX_HPP

namespace lourdes { namespace cpu {

class MutexImpl;

class Mutex
{
public:
    Mutex();
    ~Mutex();
    
    void lock();
    void unlock();

private:
    MutexImpl* impl;
};

}}

#endif // __LOURDES_CPU_MUTEX_HPP
