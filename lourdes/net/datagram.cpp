#include "datagram.hpp"

#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace lourdes { namespace net {

size_t broadcast(unsigned short port, const char* data, int length)
{
    boost::asio::io_service io_service;
    boost::system::error_code ec;

    boost::asio::ip::udp::socket socket(io_service);
    socket.open(boost::asio::ip::udp::v4(), ec);
    socket.set_option(boost::asio::ip::udp::socket::reuse_address(true), ec);
    socket.set_option(boost::asio::socket_base::broadcast(true), ec);

    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address_v4::broadcast(), port);

    return socket.send_to(boost::asio::buffer(data, length), endpoint, 0, ec);
}

size_t unicast(const char* hostname, unsigned short port, const char* data, int length)
{
    boost::asio::io_service io_service;
    boost::system::error_code ec;

    boost::asio::ip::udp::socket socket(io_service);
    socket.open(boost::asio::ip::udp::v4(), ec);
    socket.set_option(boost::asio::ip::udp::socket::reuse_address(true), ec);

    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address_v4::from_string(hostname, ec), port);

    return socket.send_to(boost::asio::buffer(data, length), endpoint, 0, ec);
}

size_t receive(unsigned short port, char* data, int length)
{
    boost::asio::io_service io_service;
    boost::system::error_code ec;

    boost::asio::ip::udp::socket socket(io_service);
    socket.open(boost::asio::ip::udp::v4(), ec);
    socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port), ec);

    if (ec)
        return 0;

    // Receive data
    boost::asio::ip::udp::endpoint endpoint;
    size_t rv = socket.receive_from(boost::asio::buffer(data, length), endpoint, 0, ec);
    socket.close(ec);

    return rv;
}

}}
