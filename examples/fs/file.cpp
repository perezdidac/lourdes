#include "file.hpp"

#include <iostream>

#include <lourdes/fs/file.hpp>

namespace lourdes { namespace examples { namespace fs {

void writeToFile()
{
    // Prepare required variables and objects
    lourdes::fs::File file;

    if (!file.open("filename"))
    {
        std::cout << "Could not open the file" << std::endl;
        return;
    }

    // Write and close
    file.write("hola", 5);
    file.close();
}

}}}
