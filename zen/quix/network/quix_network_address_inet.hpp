#ifndef __ZEN__QUIX_NETWORK_ADDRESS_INET__HPP
#define __ZEN__QUIX_NETWORK_ADDRESS_INET__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_network.h>
#include <netinet/in.h>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
class zen::quix_network_address_inet
{
    sockaddr_in sockaddr_in_mem;

public:

    quix_network_address_inet( const std::string & );

    const struct sockaddr *
    addr();

    std::size_t
    size();
};
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_NETWORK_ADDRESS_INET__HPP