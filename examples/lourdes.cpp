#include "chrono/chrono.hpp"
#include "cpu/cpu.hpp"

int main(int argc, char* argv[])
{
    // Test chrono
    lourdes::examples::chrono::printLocalTime();
    lourdes::examples::chrono::printUniversalTime();

    // Test cpu
    lourdes::examples::cpu::lockAndUnlock();
    lourdes::examples::cpu::sleepAndPrint();
    lourdes::examples::cpu::countTime();

    // Test log

    // Test net

    return 0;
}
