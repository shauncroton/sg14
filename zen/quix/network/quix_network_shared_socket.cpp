///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/network/quix_network_shared_socket.hpp>
#include <zen/quix/network/quix_network_socket_listening.hpp>
#include <zen/quix/network/quix_network_socket_connected.hpp>
#include <zen/quix/network/quix_network_address_inet.hpp>
#include <zen/quix/network/quix_network_address_unix.hpp>
#include <utility>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct zen::quix_network_shared_socket::impl
{
    quix_network_socket_connected< quix_network_address_unix > connected_quix_messaging_unix;

    impl( const std::string & );
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_socket::impl::impl( const std::string &listening_quix_messaging_unix_arg )
    : connected_quix_messaging_unix( quix_network_socket_listening< quix_network_address_unix >( listening_quix_messaging_unix_arg ).accept())
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_socket::quix_network_shared_socket( const std::string &listening_quix_messaging_unix_arg )
    : pimpl( new impl( listening_quix_messaging_unix_arg ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_socket::~quix_network_shared_socket()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_socket::socket_type_ptr
zen::quix_network_shared_socket::operator()()
{ return std::make_shared< socket_type >( pimpl->connected_quix_messaging_unix.recv_fd_checked( 0xCAFEBABEDEADBEEF )); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
to_string( const zen::quix_network_shared_socket &quix_network_shared_socketarg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
