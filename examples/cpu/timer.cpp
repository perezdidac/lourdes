#include "timer.hpp"

#include <iostream>

#include <lourdes/cpu/timer.hpp>
#include <lourdes/cpu/sleep.hpp>

namespace lourdes { namespace examples { namespace cpu {

void countTime()
{
    // Prepare required variables and objects
    lourdes::cpu::Timer timer;

    // Sleep for a while
    lourdes::cpu::sleep(1000);

    // Count time and print
    int elapsed = timer.elapsed();
    std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
}

}}}
