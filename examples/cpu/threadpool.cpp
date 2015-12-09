#include "threadpool.hpp"

#include <iostream>

#include <lourdes/cpu/threadpool.hpp>
#include <lourdes/cpu/mutex.hpp>
#include <lourdes/cpu/sleep.hpp>

namespace lourdes { namespace examples { namespace cpu {

class ExampleJob : public lourdes::cpu::ThreadJob
{
public:
    ExampleJob(unsigned int id, int sleepTime, lourdes::cpu::Mutex& mutex)
        : mutex(mutex)
    {
        this->id = id;
        this->sleepTime = sleepTime;
    }

    void process()
    {
        lourdes::cpu::sleep(sleepTime);

        // Enter mutual exclusion
        mutex.lock();

        // Print something
        std::cout << "This is the job with id " << id << " after sleeping " << sleepTime << " ms" << std::endl;

        // Leave mutual exclusion
        mutex.unlock();
    }

private:
    lourdes::cpu::Mutex& mutex;
    unsigned int id;
    int sleepTime;
};

void launchJobs()
{
    // Prepare required variables and objects
    lourdes::cpu::Mutex mutex;

    // Initialize thread pool with 4 workers
    lourdes::cpu::ThreadPool threadPool(4);

    // Add some jobs
    for (unsigned int k = 0; k < 24; ++k)
    {
        int sleepTime = (k * 100) % 500;
        ExampleJob* exampleJob = new ExampleJob(k, sleepTime, mutex);
        threadPool.addThreadJob(exampleJob);
    }

    // Start the thread
    threadPool.start();

    // Wait until the jobs finish and quit
    threadPool.stop();
}

}}}
