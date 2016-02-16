#include "unique.hpp"

#include <iostream>

#include <lourdes/fs/unique.hpp>

namespace lourdes { namespace examples { namespace fs {

void printUniqueFilename()
{
    // Generate an unique file name
    char filename[256];
    lourdes::fs::unique(filename);

    // Print the file name and quit
    std::cout << filename << std::endl;
}

}}}
