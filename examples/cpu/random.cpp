#include "random.hpp"

#include <iostream>

#include <lourdes/cpu/random.hpp>

namespace lourdes { namespace examples { namespace cpu {

void randomAndPrint()
{
    // Generate a random string
    char str[32];
    lourdes::cpu::random(str, 16);

    // Print something and quit
    std::cout << str << std::endl;
}

}}}
