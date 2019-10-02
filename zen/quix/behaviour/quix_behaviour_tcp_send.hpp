//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef __ZEN__QUIX_BEHAVIOUR_quix_behaviour_tcp_send__HPP
#define __ZEN__QUIX_BEHAVIOUR_quix_behaviour_tcp_send__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_behaviour.h>
#include <zen/quix/network/quix_network_shared_socket.hpp>
#include <zen/quix/structure/quix_structure_buffer.hpp>
#include <stdexcept>
#include <stdio.h> // printf
#include <stdlib.h> //exit
#include <unistd.h> // write/close
#include <errno.h> //errno
#include <string.h> //strerror
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>
#include <string>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
class zen::quix_behaviour_tcp_send
{
    struct impl;
    impl *pimpl;

public:

    using event_type = E;

    quix_behaviour_tcp_send( const std::string & );

    quix_behaviour_tcp_send( const quix_behaviour_tcp_send & ) = delete;

    quix_behaviour_tcp_send( quix_behaviour_tcp_send && ) = delete;

    quix_behaviour_tcp_send &
    operator=( quix_behaviour_tcp_send ) = delete;

    quix_behaviour_tcp_send &
    operator=( quix_behaviour_tcp_send && ) = delete;

    ~quix_behaviour_tcp_send();

    void
    operator()( event_type & );

    bool
    post();
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
struct zen::quix_behaviour_tcp_send< E >::impl
{
    using event_type = E;

    zen::quix_network_shared_socket sender_mem;

    impl( const std::string & );

    void
    operator()( event_type &event );

    bool
    post();
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_tcp_send< E >::impl::impl(
    const std::string &address_arg
)
    : sender_mem( address_arg )
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
void
zen::quix_behaviour_tcp_send< E >::impl::operator()(
    event_type &event
)
{
    //sender_mem.send( event.buffer_mem->data, event.buffer_mem->size );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
bool
zen::quix_behaviour_tcp_send< E >::impl::post()
{
    return true;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_tcp_send< E >::quix_behaviour_tcp_send(
    const std::string &address_arg
)
    : pimpl(
    new impl(
        address_arg
    ))
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_tcp_send< E >::~quix_behaviour_tcp_send()
{
    delete pimpl;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
void
zen::quix_behaviour_tcp_send< E >::operator()(
    event_type &event
)
{
    return pimpl->operator()( event );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
bool
zen::quix_behaviour_tcp_send< E >::post()
{
    return pimpl->post();
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
std::string
to_string(
    const zen::quix_behaviour_tcp_send< E > &tcp_send_arg
)
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_BEHAVIOUR_TCP_SEND__HPP
