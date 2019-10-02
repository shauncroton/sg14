#ifndef __ZEN__QUIX_NETWORK_SOCKET_LISTENING_HPP
#define __ZEN__QUIX_NETWORK_SOCKET_LISTENING_HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_network.h>
#include <utility>
#include <stdexcept>
#include <unistd.h> // write/close
#include <errno.h> //errno
#include <string.h> //strerror
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr_in
#include <sys/un.h>
#include <arpa/inet.h>
#include <signal.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
class zen::quix_network_socket_listening
{
    struct impl;
    impl *pimpl;

public:

    quix_network_socket_listening( const std::string & );

    quix_network_socket_listening( const quix_network_socket_listening & ) = delete;

    quix_network_socket_listening( quix_network_socket_listening && ) = delete;

    quix_network_socket_listening &
    operator=( quix_network_socket_listening ) = delete;

    quix_network_socket_listening &
    operator=( quix_network_socket_listening && ) = delete;

    ~quix_network_socket_listening();

    int
    accept();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
struct zen::quix_network_socket_listening< A >::impl
{
    using address_type =
    A;

    int fd_mem{ 0 };

    impl( const std::string & );

    ~impl();

    int
    accept();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
zen::quix_network_socket_listening< A >::impl::impl( const std::string &address_arg )
{
    unlink( address_arg.c_str());
    address_type address( address_arg );

    if(( fd_mem = socket(
        address.addr()->sa_family,
        SOCK_STREAM,
        0
    )) < 0 )
    {
        std::string what( "Failed create listen socket for port: " );
        what += "[" + address_arg + "] ";
        throw std::runtime_error(( what + strerror(errno)).c_str());
    }

    if( bind(
        fd_mem,
        address.addr(),
        address.size()) < 0 )
    {
        close( fd_mem );
        std::string what( "Failed create listen socket for port: " );
        what += "[" + address_arg + "] ";
        throw std::runtime_error(( what + strerror(errno)).c_str());
    }

    if( listen(
        fd_mem,
        1024
    ) < 0 )
    {
        close( fd_mem );
        std::string what( "Failed to bind listen socket: " );
        what += "[" + address_arg + "] ";
        throw std::runtime_error(( what + strerror(errno)).c_str());
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
zen::quix_network_socket_listening< A >::impl::~impl()
{ close( fd_mem ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
int
zen::quix_network_socket_listening< A >::impl::accept()
{
    int fd_new;

    if(( fd_new = ::accept(
        fd_mem,
        ( struct sockaddr * ) 0,
        0
    )) < 0 )
    {
        std::string what( "Failed to accept incoming connection on port: " );
        throw std::runtime_error(( what + strerror(errno)).c_str());
    }

    return fd_new;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
zen::quix_network_socket_listening< A >::quix_network_socket_listening( const std::string &address_arg )
    : pimpl( new impl( address_arg ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
zen::quix_network_socket_listening< A >::~quix_network_socket_listening()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
int
zen::quix_network_socket_listening< A >::accept()
{ return pimpl->accept(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename A >
std::string
to_string( const zen::quix_network_socket_listening< A > &quix_network_socket_listening_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_NETWORK_SOCKET_LISTENING_HPP
