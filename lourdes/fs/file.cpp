#include "file.hpp"

#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif


namespace lourdes { namespace fs {

class FileImpl
{
public:
    FILE* file;
};

File::File()
{
    impl = new FileImpl;
    impl->file = NULL;
}

File::~File()
{
    close();
    delete impl;
}

bool File::open(const char* filename, OpenMode openMode)
{
    if (impl->file != NULL)
        return false;

    char* mode;
    if (openMode == OPEN_MODE_READ)
        mode = "rb";
    else if (openMode == OPEN_MODE_WRITE)
        mode = "wb";
    else
        return false;

    impl->file = fopen(filename, mode);

    return impl->file != NULL;
}

bool File::read(char* buffer, int length)
{
    if (impl->file == NULL)
        return false;

    fread(buffer, 1, length, impl->file);

    return true;
}

bool File::write(const char* buffer, int length)
{
    if (impl->file == NULL)
        return false;

    fwrite(buffer, 1, length, impl->file);

    return true;
}

void File::close()
{
    if (impl->file == NULL)
        return;
    
    fclose(impl->file);
    impl->file = NULL;
}

}}
