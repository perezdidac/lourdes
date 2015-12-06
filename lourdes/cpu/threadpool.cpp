#include "threadpool.hpp"

//TODO: remove this dependency if possible
#include <vector>

#include "mutex.hpp"
#include "sleep.hpp"

namespace lourdes { namespace cpu {
    
class Worker : public lourdes::cpu::Thread
{
public:
    Worker::Worker()
    {
        // Initialize variables
        threadJob = NULL;
    }

    void stop()
    {
        running = false;
        join();
    }

    bool Worker::busy()
    {
        mutex.lock();
        bool busy = threadJob != NULL;
        mutex.unlock();
        return busy;
    }

    void Worker::setThreadJob(ThreadJob* threadJob)
    {
        mutex.lock();
        this->threadJob = threadJob;
        mutex.unlock();
    }

    void Worker::run()
    {
        running = true;

        // Thread pool main loop
        for (;;)
        {
            if (threadJob != NULL)
            {
                // Process the thread job
                threadJob->process();
                delete threadJob;
                threadJob = NULL;

                // Sleep for a while just for avoid overloading the CPU
                lourdes::cpu::sleep(10);
                continue;
            }

            // Check if must exit
            if (!running)
                break;

            // Sleep for a while just for avoid overloading the CPU
            lourdes::cpu::sleep(10);
        }
    }

public:
    ThreadJob* threadJob;
    lourdes::cpu::Mutex mutex;
    bool running;
};

class ThreadPoolImpl : public lourdes::cpu::Thread
{
public:
    void run()
    {
        // Launch the worker threads
        for (int k = 0; k < numThreads; ++k)
        {
            Worker* worker = new Worker;
            worker->start();
            workers.push_back(worker);
        }

        ThreadJob* threadJob = NULL;

        // Thread pool main loop
        for (;;)
        {
            // Check if there are elements to process in the queue
            if (threadJob == NULL)
                threadJob = getThreadJob();

            if (threadJob != NULL)
            {
                // In this case, the job must be passed to a thread
                for (int k = 0; k < numThreads; ++k)
                {
                    Worker* worker = workers[k];

                    if (!worker->busy())
                    {
                        worker->setThreadJob(threadJob);
                        threadJob = NULL;
                        break;
                    }
                }

                continue;
            }

            // Check if must exit
            if (!running)
                break;

            // Wait a couple of milliseconds just for avoid overloading the CPU
            lourdes::cpu::sleep(10);
        }

        if (threadJob != NULL)
            // Remove the last thread job if was not processed
            delete threadJob;

        // Stop all the worker threads and clean everything
        for (int k = 0; k < numThreads; ++k)
        {
            Worker* worker = workers[k];
            worker->stop();
            delete worker;
        }
    }

    void addThreadJob(ThreadJob* threadJob)
    {
        mutex.lock();
        threadJobs.push_back(threadJob);
        mutex.unlock();
    }

    ThreadJob* getThreadJob()
    {
        ThreadJob* threadJob = NULL;

        mutex.lock();
        if (!threadJobs.empty())
        {
            // Get the first job in the queue and remove it from the list
            threadJob = threadJobs.front();
            threadJobs.erase(threadJobs.begin() + 0);
        }
        mutex.unlock();

        return threadJob;
    }

public:
    int numThreads;
    std::vector<Worker*> workers;
    std::vector<ThreadJob*> threadJobs;
    lourdes::cpu::Mutex mutex;
    bool running;
};

ThreadPool::ThreadPool(int numThreads)
{
    impl = new ThreadPoolImpl;
    impl->numThreads = numThreads < 1 ? 1 : numThreads;
    impl->running = false;
}

ThreadPool::~ThreadPool()
{
    stop();
    delete impl;
}

void ThreadPool::start()
{
    if (impl->running)
        return;

    impl->start();
}

void ThreadPool::stop()
{
    impl->running = false;
    impl->join();
}

void ThreadPool::addThreadJob(ThreadJob* threadJob)
{
    impl->addThreadJob(threadJob);
}

}}
