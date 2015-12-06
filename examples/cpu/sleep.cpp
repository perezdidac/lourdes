#include "sleep.hpp"

#include <iostream>

#include <lourdes/cpu/sleep.hpp>

namespace lourdes { namespace examples { namespace cpu {

void sleepAndPrint()
{
    // Sleep for a while
    lourdes::cpu::sleep(1000);

    // Print something and quit
    std::cout << "Slept for a while" << std::endl;
}

}}}
