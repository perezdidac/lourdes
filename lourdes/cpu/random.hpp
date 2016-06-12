#ifndef __LOURDES_CPU_RANDOM_HPP
#define __LOURDES_CPU_RANDOM_HPP

/// \example    examples/cpu/random.cpp
namespace lourdes { namespace cpu {

/// \brief  Returns a random string with the given length.
/// \param  str     Input string that will be filled with random characters.
/// \param  len     Number of characters to generate.
void random(char* str, int len);

}}

#endif // __LOURDES_CPU_RANDOM_HPP
