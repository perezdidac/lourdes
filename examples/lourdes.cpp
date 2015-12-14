#include "chrono/chrono.hpp"
#include "cpu/cpu.hpp"
#include "fs/fs.hpp"
#include "log/log.hpp"
#include "net/net.hpp"

int main(int argc, char* argv[])
{
    // Test chrono
    lourdes::examples::chrono::printLocalTime();
    lourdes::examples::chrono::printUniversalTime();

    // Test cpu
    lourdes::examples::cpu::lockAndUnlock();
    lourdes::examples::cpu::sleepAndPrint();
    lourdes::examples::cpu::countTime();
    lourdes::examples::cpu::createThread();
    lourdes::examples::cpu::launchJobs();

    // Test fs
    lourdes::examples::fs::writeToFile();
    lourdes::examples::fs::readFromFile();

    // Test log
    // ...

    // Test net
    lourdes::examples::net::http::getFile();

    return 0;
}
