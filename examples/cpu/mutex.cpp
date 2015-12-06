#include "mutex.hpp"

#include <iostream>

#include <lourdes/cpu/mutex.hpp>

namespace lourdes { namespace examples { namespace cpu {

void lockAndUnlock()
{
    // Prepare required variables and objects
    lourdes::cpu::Mutex mutex;

    // Enter mutual exclusion
    mutex.lock();

    // Do stuff
    // ...

    // Leave mutual exclusion
    mutex.unlock();
}

}}}
