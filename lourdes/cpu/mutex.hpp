#ifndef __LOURDES_CPU_MUTEX_HPP
#define __LOURDES_CPU_MUTEX_HPP

/// \example    examples/cpu/mutex.cpp
namespace lourdes { namespace cpu {

class MutexImpl;

/// \brief  Represents a mutual exclusion object with atomic lock() and unlock()
/// operations. Multiple threads can try to lock the object, but only one can
/// actually have the mutual exclusion.
class Mutex
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    Mutex();

    /// \brief  Destroys the object and all the associated resources to it.
    ~Mutex();
    
    /// \brief  Locks the mutual exclusion object. If already locked, blocks
    /// until other thread unlocks it and no other threads also locks the
    /// object.
    void lock();

    /// \brief  Unlocks the mutual exclusion object. If one or more threads are
    /// blocked trying to lock it, one of them is notified and can lock the
    /// object.
    void unlock();

private:
    Mutex(Mutex const&);
    Mutex& operator=(Mutex const&);
    MutexImpl* impl;
};

}}

#endif // __LOURDES_CPU_MUTEX_HPP
