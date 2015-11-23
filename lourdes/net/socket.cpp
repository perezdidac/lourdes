#include "socket.hpp"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

namespace lourdes { namespace net {

static boost::asio::io_service io_service;

class SessionImpl
{
public:
    SessionImpl(boost::asio::io_service& io_service)
        : socket_(io_service) {};

public:
    boost::asio::ip::tcp::socket socket_;
};

Session::Session()
{
    impl = new SessionImpl(io_service);
}

Session::~Session()
{
    close();
    delete impl;
}

size_t Session::read(char* data, size_t size)
{
    boost::system::error_code ec;
    size_t bytes_transferred = impl->socket_.read_some(boost::asio::buffer(data, size), ec);
    return bytes_transferred;
}

size_t Session::write(const char* data, size_t size)
{
    boost::system::error_code ec;
    size_t bytes_transferred = boost::asio::write(impl->socket_, boost::asio::buffer(data, size), ec);
    return bytes_transferred;
}

void Session::close()
{
    boost::system::error_code ec;
    impl->socket_.close(ec);
}

bool Session::connect(const char* hostname, unsigned short port)
{
    boost::system::error_code ec;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(hostname, boost::lexical_cast<std::string>(port));
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query, ec);

    if (ec)
        return false;

    boost::asio::connect(impl->socket_.lowest_layer(), iterator, ec);

    return !ec;
}

class ServerImpl
{
public:
    ServerImpl();
    ~ServerImpl();

public:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::acceptor* acceptor_;
};

Server::Server()
{
    impl->acceptor_ = NULL;
}

Server::~Server()
{
    close();

    if (impl->acceptor_ != NULL)
    {
        delete impl->acceptor_;
        impl->acceptor_ = NULL;
    }
}

void Server::close()
{
    if (impl->acceptor_ == NULL)
        return;

    boost::system::error_code ec;
    impl->acceptor_->close(ec);
}

}}
