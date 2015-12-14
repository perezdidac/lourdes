#include "thread.hpp"

#include <boost/thread.hpp>

#ifndef NULL
#define NULL 0
#endif

namespace lourdes { namespace cpu {

class ThreadImpl
{
public:
    boost::thread* thread;
};

void threadStart(Thread* This)
{
    This->run();
}

Thread::Thread()
{
    impl = new ThreadImpl;
    impl->thread = NULL;
}

Thread::~Thread()
{
    if (impl->thread != NULL)
        join();

    delete impl;
}

void Thread::start()
{
    // Start the thread
    if (impl->thread != NULL)
        return;

    impl->thread = new boost::thread(threadStart, this);
}

void Thread::join()
{
    if (impl->thread == NULL)
        return;
    
    impl->thread->join();
    delete impl->thread;
    impl->thread = NULL;
}

}}
