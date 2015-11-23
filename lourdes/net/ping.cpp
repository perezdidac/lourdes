#include "ping.hpp"

#include "socket.hpp"

#include <boost/asio.hpp>

namespace lourdes { namespace net {
    
extern boost::asio::io_service io_service;

bool ping(const char* hostname)
{
    // Prepare and resolve the host name
    boost::asio::ip::icmp::resolver::query query(boost::asio::ip::icmp::v4(), hostname, "");
    boost::asio::ip::icmp::resolver resolver(io_service);
    boost::system::error_code ec;
    boost::asio::ip::icmp::endpoint destination = resolver.resolve(query, ec)->endpoint();
    if (ec)
        return false;

    // Prepare the ICMP packet
    const int length = 256;
    char data[length];
    memset(data, 0xff, length);

    // Send the ICMP packet
    boost::asio::ip::icmp::socket socket(io_service, boost::asio::ip::icmp::v4());
    socket.send_to(boost::asio::buffer(data, length), destination);

    // Wait for a reply
    return true;
}

}}
