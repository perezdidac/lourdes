#ifndef __LOURDES_CPU_SLEEP_HPP
#define __LOURDES_CPU_SLEEP_HPP

/// \example    examples/cpu/sleep.cpp
namespace lourdes { namespace cpu {

/// \brief  Blocks for the given amount of time in milliseconds.
/// \param  milliseconds    Time, in milliseconds, to block before return.
void sleep(int milliseconds);

}}

#endif // __LOURDES_CPU_SLEEP_HPP
