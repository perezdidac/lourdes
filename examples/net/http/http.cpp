#include "http.hpp"

#include <iostream>

#include <lourdes/net/http/http.hpp>

namespace lourdes { namespace examples { namespace net { namespace http {

void getFile()
{
    // Prepare required variables and objects
    char* hostname = "www.didacperez.cat";
    char* path = "/img/didac.jpg";
    char* filename = "didac.jpg";

    // Get the file
    lourdes::net::http::get(hostname, path, filename);
}

}}}}
