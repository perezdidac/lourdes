#ifndef __LOURDES_NET_PING_HPP
#define __LOURDES_NET_PING_HPP

namespace lourdes { namespace net {

/// \brief  Tries to ping a given hostname using a simple ICMP packet. This
/// method will try to resolve host names in the case the hostname parameter is
/// not an IP address.
/// \param  hostname    Remote host name or IP address represented as a string.
/// \return A flag which indicates if the operation has succeed.
bool ping(const char* hostname);

}}

#endif // __LOURDES_NET_PING_HPP
