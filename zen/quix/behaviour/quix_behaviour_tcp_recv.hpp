//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifndef __ZEN__QUIX_BEHAVIOUR_TCP_RECV__HPP
#define __ZEN__QUIX_BEHAVIOUR_TCP_RECV__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_behaviour.h>
#include <zen/quix/structure/quix_structure_event.hpp>
#include <zen/quix/structure/quix_structure_buffer.hpp>
#include <zen/quix/network/quix_network_shared_socket.hpp>
#include <stdexcept>
#include <string>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
class zen::quix_behaviour_tcp_recv
{
    struct impl;
    impl *pimpl;

public:

    using event_type = E;

    quix_behaviour_tcp_recv(
        void *,
        const std::string &
    );

    quix_behaviour_tcp_recv( const quix_behaviour_tcp_recv & ) = delete;

    quix_behaviour_tcp_recv( quix_behaviour_tcp_recv && ) = delete;

    quix_behaviour_tcp_recv &
    operator=( quix_behaviour_tcp_recv ) = delete;

    quix_behaviour_tcp_recv &
    operator=( quix_behaviour_tcp_recv && ) = delete;

    ~quix_behaviour_tcp_recv();

    void
    operator()( event_type & );

    bool
    post();
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
struct zen::quix_behaviour_tcp_recv< E >::impl
{
    static constexpr int pool_quix_messaging_slot_count{ 256 };
    static constexpr int pool_mask{ pool_quix_messaging_slot_count - 1 };

    using event_type = E;
    using buffer_type = typename event_type::buffer_type;

    struct data_type
    {
        alignas( 64 ) int pool_quix_messaging_slot_cursor;
        alignas( 64 ) buffer_type buffer_pool[pool_quix_messaging_slot_count];
    };

    data_type *data_mem;
    zen::quix_network_shared_socket receiver_mem;

    impl(
        data_type *,
        const std::string &
    );

    void
    operator()( event_type & );

    bool
    post();
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_tcp_recv< E >::impl::impl(
    data_type *data_arg,
    const std::string &address_arg
)
    : data_mem( data_arg )
    , receiver_mem( address_arg )
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
void
zen::quix_behaviour_tcp_recv< E >::impl::operator()(
    event_type &event
)
{
    event.buffer_mem = &data_mem->buffer_pool[ ++data_mem->pool_quix_messaging_slot_cursor ];
    //event.buffer_mem->size = receiver_mem.recv( event.buffer_mem->data, event.buffer_mem->reserved );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
bool
zen::quix_behaviour_tcp_recv< E >::impl::post()
{
    return true;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_tcp_recv< E >::quix_behaviour_tcp_recv(
    void *data_arg,
    const std::string &address_arg
)
    : pimpl(
    new impl(
        reinterpret_cast< typename impl::data_type * >( data_arg ),
        address_arg
    ))
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_tcp_recv< E >::~quix_behaviour_tcp_recv()
{
    delete pimpl;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
void
zen::quix_behaviour_tcp_recv< E >::operator()(
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
zen::quix_behaviour_tcp_recv< E >::post()
{
    return pimpl->post();
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
std::string
to_string(
    const zen::quix_behaviour_tcp_recv< E > &quix_behaviour_tcp_recv_arg
)
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_BEHAVIOUR_TCP_RECV__HPP
