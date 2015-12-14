#ifndef __LOURDES_NET_HTTP_HPP
#define __LOURDES_NET_HTTP_HPP

/// \brief  Holds methods for communicating to a web server via HTTP.
namespace lourdes { namespace net { namespace http {

/// \brief  Tries to fetch data from the given URL.
/// \param  hostname    The name of the host to connect to.
/// \param  path        URL path to get from.
/// \param  filename    Filename of the file in which the data will be saved.
/// \return A flag which indicates if the operation has succeed.
bool get(const char* hostname, const char* path, const char* filename);

}}}

#endif // __LOURDES_NET_HTTP_HPP
