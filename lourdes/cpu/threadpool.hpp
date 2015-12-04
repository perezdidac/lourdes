#ifndef __LOURDES_CPU_THREADPOOL_HPP
#define __LOURDES_CPU_THREADPOOL_HPP

#include "thread.hpp"

namespace lourdes { namespace cpu {

class ThreadPoolImpl;

/// \brief  Represents a task that could be executed by a ThreadPool.
class ThreadJob
{
public:
    /// \brief  Destroys the object and all the associated resources to it.
    virtual ~ThreadJob() { }

    /// \brief  Executes the job.
    virtual void process() = 0;
};

/// \brief  Represents an object which can be used as a task executor based on
/// a pool of worker threads which execute the queued jobs in parallel.
class ThreadPool
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    /// \param  numThreads  Specifies the number of worker threads to be
    /// executed.
    ThreadPool(int numThreads);

    /// \brief  Destroys the object and all the associated resources to it.
    ~ThreadPool();

    /// \brief  Starts the thread pool.
    void start();

    /// \brief  Stops the thread pool by stopping all the worker threads and the
    /// main master thread.
    void stop();

    /// \brief  Adds a thread job to the queue.
    /// \param  threadJob   A pointer to the thread job to be added to the
    /// queue.
    /// \return A flag which indicates if the thread job has been aded.
    bool addThreadJob(ThreadJob* threadJob);
    
private:
    ThreadPoolImpl* impl;
};

}}

#endif // __LOURDES_CPU_THREADPOOL_HPP
