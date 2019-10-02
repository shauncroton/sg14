#ifndef __ZEN__QUIX_BEHAVIOUR__H
#define __ZEN__QUIX_BEHAVIOUR__H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace zen
{
    template< typename E >
    class quix_behaviour_base;

    template< typename E >
    class quix_behaviour_event_consume;

    template< typename E >
    class quix_behaviour_event_publish;

    template< typename E >
    class quix_behaviour_event_republish;

    template< typename E >
    class quix_behaviour_file_read;

    template< typename E >
    class quix_behaviour_file_write;

    template< typename E >
    class quix_behaviour_tcp_recv;

    template< typename E >
    class quix_behaviour_tcp_send;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_BEHAVIOUR__H
