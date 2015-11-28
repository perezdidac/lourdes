#ifndef __LOURDES_NET_SOCKET_HPP
#define __LOURDES_NET_SOCKET_HPP

#include <stdlib.h>

namespace lourdes { namespace net {

class SessionImpl;
class ServerImpl;

/// \brief  Represents a TCP/IP session which provides basic I/O functions such
/// as read(), write(), close() and connect().
class Session
{
    friend class Server;

public:
    /// \brief  Initializes the object and all the associated resources to it.
    Session();
    
    /// \brief  Destroys the object and all the associated resources to it. If
    /// the current connection is alive, it closes it.
    ~Session();

    /// \brief  Blocks until the given amount of data is read from the socket,
    /// measured in bytes.
    /// \param  data    A pointer where the data starts from.
    /// \param  size    Total amount of bytes to be read to the socket.
    /// \return The total amount of bytes read from the socket. If it does not
    /// correspond to the data to be sent, it means that the connection has been
    /// closed.
    size_t read(char* data, size_t size);
    
    /// \brief  Blocks until the given amount of data is written to the socket,
    /// measured in bytes.
    /// \param  data    A pointer where the data starts from.
    /// \param  size    Total amount of bytes to be written to the socket.
    /// \return The total amunt of bytes written to the socket. If it does not
    /// correspond to the data to be read, it means that the connection has been
    /// closed.
    size_t write(const char* data, size_t size);

    /// \brief  Closes the connection, cancelling the current I/O operations.
    void close();

    /// \brief  Tries to connect to a given host using the given port number.
    /// \param  hostname    Remote host name or IP address represented as a
    /// string.
    /// \param  port        The TCP/IP port used to establish the connection.
    /// \return A flag that indicates if the connection has been established.
    bool connect(const char* hostname, unsigned short port);

private:
    SessionImpl* impl;
};

/// \brief  Represents a TCP/IP server which listens for incoming connections.
class Server
{
public:
    /// \brief  Initializes the object and all the associated resources to it.
    Server();

    /// \brief  Destroys the object and all the associated resources to it.
    ~Server();

    /// \brief  Starts listening from the given port. After that, the accept()
    /// method may be called to get incoming connections.
    /// \param  port    The TCP/IP port to listen to.
    /// \return A flag that indicates if the socket can listen to the given
    /// port.
    bool listen(unsigned short port);

    /// \brief  Tries to get an incoming connection. If not, it returns
    /// immediately with a NULL return value.
    /// \return If an incoming connection arrives, it returns a Session object
    /// which represents the established connection. Otherwise, a NULL value is
    /// returned.
    Session* accept();

    /// \brief  Stops listening and closes the listening socket.
    void close();

private:
    ServerImpl* impl;
};

}}

#endif // __LOURDES_NET_SOCKET_HPP
