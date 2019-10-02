#ifndef __ZEN__QUIX_NETWORK__H
#define __ZEN__QUIX_NETWORK__H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace zen
{
    class quix_network_address_inet;

    class quix_network_address_unix;

    class quix_network_shared_listener;

    class quix_network_quix_memory_shared_sender;

    class quix_network_shared_socket;

    template< typename A >
    class quix_network_socket_connected;

    template< typename A >
    class quix_network_socket_listening;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_NETWORK__H
