#include "file.hpp"

namespace lourdes { namespace fs {

class FileImpl
{
public:
};

File::File()
{
    impl = new FileImpl;
}

File::~File()
{
    delete impl;
}

}}
