///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/network/quix_network_shared_listener.hpp>
#include <zen/quix/network/quix_network_socket_listening.hpp>
#include <zen/quix/network/quix_network_socket_connected.hpp>
#include <zen/quix/network/quix_network_address_inet.hpp>
#include <zen/quix/network/quix_network_address_unix.hpp>
#include <utility>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct zen::quix_network_shared_listener::impl
{
    quix_network_socket_listening< quix_network_address_inet > listening_inet;
    quix_network_socket_connected< quix_network_address_unix > connected_quix_messaging_unix_receiver;
    quix_network_socket_connected< quix_network_address_unix > connected_quix_messaging_unix_sender;

    impl(
        const std::string &,
        const std::string &,
        const std::string &
    );
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_listener::impl::impl(
    const std::string &listening_inet_arg,
    const std::string &connected_quix_messaging_unix_receiver_arg,
    const std::string &connected_quix_messaging_unix_sender_arg
)
    : listening_inet( listening_inet_arg )
    , connected_quix_messaging_unix_receiver( connected_quix_messaging_unix_receiver_arg )
    , connected_quix_messaging_unix_sender( connected_quix_messaging_unix_sender_arg )
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_listener::quix_network_shared_listener(
    const std::string &listening_inet_arg,
    const std::string &receiving_quix_messaging_unix_arg,
    const std::string &sending_quix_messaging_unix_arg
)
    : pimpl(
    new impl(
        listening_inet_arg,
        receiving_quix_messaging_unix_arg,
        sending_quix_messaging_unix_arg
    ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_network_shared_listener::~quix_network_shared_listener()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::quix_network_shared_listener::operator()()
{
    int fd = pimpl->listening_inet.accept();
    pimpl->connected_quix_messaging_unix_receiver.send_fd_checked(
        0xCAFEBABEDEADBEEF,
        fd
    );
    pimpl->connected_quix_messaging_unix_sender.send_fd_checked(
        0xCAFEBABEDEADBEEF,
        fd
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
to_string( const zen::quix_network_shared_listener &quix_network_shared_listenerarg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
