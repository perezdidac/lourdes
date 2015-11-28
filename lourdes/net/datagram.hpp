#ifndef __LOURDES_NET_DATAGRAM_HPP
#define __LOURDES_NET_DATAGRAM_HPP

namespace lourdes { namespace net {

/// \brief  Broadcasts an UDP datagram.
/// \param  port        UDP port used for sending the datagram.
/// \param  data        Pointer to the data that will be sent.
/// \param  length      Length of the data that will be sent.
/// \return Total number of bytes sent.
size_t broadcast(unsigned short port, const char* data, int length);

/// \brief  Sends an UDP datagram to a given address.
/// \param  hostname    Hostname or IP address used to send the datagram.
/// \param  port        UDP port used for sending the datagram.
/// \param  data        Pointer to the data that will be sent.
/// \param  length      Length of the data that will be sent.
/// \return Total number of bytes sent.
size_t unicast(const char* hostname, unsigned short port, const char* data, int length);

/// \brief  Receives UDP datagrams.
/// \param  port        UDP port used for listening for the datagram.
/// \param  data        Pointer to the place that will allocate the data.
/// \param  length      Max length of the data that will be received.
/// \return Total number of bytes received.
size_t receive(unsigned short port, char* data, int length);

}}

#endif // __LOURDES_NET_DATAGRAM_HPP
