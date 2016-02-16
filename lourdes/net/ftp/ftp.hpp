#ifndef __LOURDES_NET_FTP_HPP
#define __LOURDES_NET_FTP_HPP

/// \brief  Holds methods for communicating to FTP servers.
namespace lourdes { namespace net { namespace ftp {

/// \brief  Tries to write a file to a FTP server.
/// \param  hostname    The name of the host to connect to.
/// \param  username    The user name used to connect to the FTP server.
/// \param  password    The corresponding password for the user user name.
/// \param  path        URL path of the file to be written.
/// \param  filename    Filename of the file to be sent.
/// \return A flag which indicates if the operation has succeed.
bool set(const char* hostname, const char* username, const char* password, const char* path, const char* filename);

}}}

#endif // __LOURDES_NET_FTP_HPP
