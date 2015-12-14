#include "file.hpp"

#include <iostream>

#include <lourdes/fs/file.hpp>

namespace lourdes { namespace examples { namespace fs {

void writeToFile()
{
    // Prepare required variables and objects
    lourdes::fs::File file;

    if (!file.open("filename", lourdes::fs::File::OPEN_MODE_WRITE))
    {
        std::cout << "Could not open the file for writing" << std::endl;
        return;
    }

    // Write and close
    file.write("hola", 4);
    file.close();
}

void readFromFile()
{
    // Prepare required variables and objects
    lourdes::fs::File file;

    if (!file.open("filename", lourdes::fs::File::OPEN_MODE_READ))
    {
        std::cout << "Could not open the file for reading" << std::endl;
        return;
    }

    // Read and close
    char buffer[4];
    file.read(buffer, 4);
    file.close();
}

}}}
