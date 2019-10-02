//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef __ZEN__QUIX_NETWORK_SHARED_SOCKET__HPP
#define __ZEN__QUIX_NETWORK_SHARED_SOCKET__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_network.h>
#include <zen/quix/network/quix_network_shared_socket.hpp>
#include <zen/quix/network/quix_network_socket_connected.hpp>
#include <zen/quix/network/quix_network_address_inet.hpp>
#include <memory>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
class zen::quix_network_shared_socket
{
    struct impl;
    impl *pimpl;

public:

    using socket_type = quix_network_socket_connected< quix_network_address_inet >;
    using socket_type_ptr = std::shared_ptr< socket_type >;

    quix_network_shared_socket( const std::string & );

    quix_network_shared_socket( const quix_network_shared_socket & ) = delete;

    quix_network_shared_socket( quix_network_shared_socket && ) = delete;

    quix_network_shared_socket &
    operator=( quix_network_shared_socket ) = delete;

    quix_network_shared_socket &
    operator=( quix_network_shared_socket && ) = delete;

    ~quix_network_shared_socket();

    socket_type_ptr
    operator()();
};
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_NETWORK_SHARED_SOCKET__HPP
