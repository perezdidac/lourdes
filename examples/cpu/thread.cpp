#include "thread.hpp"

#include <iostream>

#include <lourdes/cpu/thread.hpp>

namespace lourdes { namespace examples { namespace cpu {

class ExampleThread : public lourdes::cpu::Thread
{
public:
    void run()
    {
        // Print something
        std::cout << "This is the thread" << std::endl;
    }
};

void createThread()
{
    // Prepare required variables and objects
    ExampleThread thread;

    // Start the thread
    thread.start();

    // Wait until the thread finishes
    thread.join();
}

}}}
