#include "random.hpp"

#include <cstdlib>
#include <ctime>

namespace lourdes { namespace cpu {

static const char alphanum[] =
    "0123456789abcdef";

void random(char* str, int len)
{
    srand(time(NULL));
    for (int k = 0; k < len; ++k)
    {
        str[k] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    str[len] = 0;
}

}}
