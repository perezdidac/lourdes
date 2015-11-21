#ifndef __LOURDES_SOCKET_HPP
#define __LOURDES_SOCKET_HPP

namespace lourdes {

class SessionImpl;

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

}

#endif // __LOURDES_SOCKET_HPP
