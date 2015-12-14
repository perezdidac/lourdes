#include "http.hpp"

#include "../../fs/file.hpp"

#include <boost/asio.hpp>

namespace lourdes { namespace net { namespace http {

extern boost::asio::io_service io_service;

bool get(const char* hostname, const char* path, const char* filename)
{
    boost::asio::io_service io_service;
    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(hostname, "http");
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query, ec);
    if (ec)
        return false;

    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::connect(socket, iterator, ec);
    if (ec)
        return false;

    // Send the request
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET " << path << " HTTP/1.0\r\n";
    request_stream << "Host: " << hostname << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";
    boost::asio::write(socket, request);

    // Wait for full response
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    // Check response
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);

    // Checks
    if (!response_stream)
        return false;
    if (http_version.substr(0, 5) != "HTTP/")
        return false;
    if (status_code != 200)
        return false;

    // Read the response headers, which are terminated by a blank line
    boost::asio::read_until(socket, response, "\r\n\r\n");

    // Process the response headers
    std::string header;
    while (std::getline(response_stream, header) && header != "\r") ;

    // Try to open a file for writing
    lourdes::fs::File file;
    if (!file.open(filename))
    {
        socket.close();
        return false;
    }

    // Read until EOF, writing data to output as we go
    int written = 0;
    while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), ec))
    {
        // Read data
        const char* buffer = boost::asio::buffer_cast<const char*>(response.data());
        int length = response.size();
        file.write(buffer + written, length - written);
        written = length;
    }

    // Close the file
    file.close();

    if (ec != boost::asio::error::eof)
    {
        socket.close();
        return false;
    }

    socket.close();

    return true;
}

}}}
