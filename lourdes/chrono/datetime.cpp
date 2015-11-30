#include "datetime.hpp"

#include <boost/date_time.hpp>

namespace lourdes { namespace chrono {

void local(const char* format, char* output)
{
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::local_time();
    std::stringstream stream;
    stream.imbue(std::locale(stream.getloc(), new boost::posix_time::time_facet(format)));
    stream << currentTime;
    std::string string = stream.str();
    strcpy(output, string.c_str());
}

void universal(const char* format, char* output)
{
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::universal_time();
    std::stringstream stream;
    stream.imbue(std::locale(stream.getloc(), new boost::posix_time::time_facet(format)));
    stream << currentTime;
    std::string string = stream.str();
    strcpy(output, string.c_str());
}

}}
