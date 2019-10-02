#ifndef __ZEN__QUIX_NETWORK_ADDRESS_UNIX__HPP
#define __ZEN__QUIX_NETWORK_ADDRESS_UNIX__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_network.h>
#include <netinet/in.h>
#include <sys/un.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::quix_network_address_unix
{
    sockaddr_un sockaddr_un_mem;

public:

    quix_network_address_unix( const std::string & );

    const struct sockaddr *
    addr();

    std::size_t
    size();
};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_NETWORK_ADDRESS_UNIX__HPP
