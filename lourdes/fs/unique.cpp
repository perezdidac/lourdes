#include "unique.hpp"

#include <boost/filesystem.hpp>

namespace lourdes { namespace fs {

void unique(char* filename)
{
    boost::filesystem::path path = boost::filesystem::unique_path();
    std::string tempstr = path.string();
    strcpy(filename, tempstr.c_str());
}

}}
