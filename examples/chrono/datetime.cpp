#include "datetime.hpp"

#include <iostream>

#include <lourdes/chrono/datetime.hpp>

namespace lourdes { namespace examples { namespace chrono {

void printLocalTime()
{
    // Prepare required variables and objects
    char output[32];

    // Get local time in the given format
    lourdes::chrono::local("%Y-%m-%d %H:%M:%S", output);

    // Print local time
    std::cout << output << std::endl;
}

void printUniversalTime()
{
    // Prepare required variables and objects
    char output[32];

    // Get universal time in the given format
    lourdes::chrono::universal("%Y-%m-%d %H:%M:%S", output);

    // Print universal time
    std::cout << output << std::endl;
}

}}}
