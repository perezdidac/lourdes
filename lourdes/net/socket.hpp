#ifndef __LOURDES_NET_SOCKET_HPP
#define __LOURDES_NET_SOCKET_HPP

namespace lourdes { namespace net {

class SessionImpl;
class ServerImpl;

class Session
{
public:
    Session();
    ~Session();

    size_t read(char* data, size_t size);
    size_t write(const char* data, size_t size);
    void close();
    bool connect(const char* hostname, unsigned short port);

private:
    SessionImpl* impl;
};

class Server
{
public:
    Server();
    ~Server();

    bool listen(unsigned short port);
    Session* accept();
    void close();

private:
    ServerImpl* impl;
};

}}

#endif // __LOURDES_NET_SOCKET_HPP
