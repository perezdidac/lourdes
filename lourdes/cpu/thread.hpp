#ifndef __LOURDES_CPU_THREAD_HPP
#define __LOURDES_CPU_THREAD_HPP

namespace lourdes { namespace cpu {

class ThreadImpl;

/// \brief  Represents a thread object. This class must be inherited and the
/// run() method must be implemented. The started thread will execute the run()
/// method, so the run() method may never be directly called. Multiple threads
/// can be started as long as the previous ones have been finished and cleaned
/// using the join() method.
class Thread
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    Thread();
    
    /// \brief  Destroys the object and all the associated resources to it. If
    /// the thread is still alive, blocks until it has finished.
    virtual ~Thread();

    /// \brief  Creates a thread and starts it by calling the run() function. If
    /// a thread has already been started, it does nothing unless the join()
    /// method has been called and the thread has finished.
    void start();

    /// \brief  Blocks until the thread has finished.
    void join();

public:
    /// \brief  Function that will be executed by the thread once started. This
    /// function must be implemented in the inherited class.
    virtual void run() = 0;
    
private:
    ThreadImpl* impl;
};

}}

#endif // __LOURDES_CPU_THREAD_HPP
