#ifndef __ZEN__QUIX_TRANSPORT_LWD__HPP
#define __ZEN__QUIX_TRANSPORT_LWD__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_messaging.h>
#include <zen/quix/structure/quix_structure_cacheline.hpp>
#include <stdexcept>
#include <thread>
#include <vector>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
class zen::quix_messaging_lwd
{
    static_assert(
        std::is_pod< E >::value,
        "Event type must be POD"
    );

    struct impl;
    impl *pimpl;

public:

    using node_id_type =
    unsigned int;
    using follow_list_type =
    std::vector< unsigned int >;
    using event_type =
    E;

    quix_messaging_lwd(
        void *,
        const node_id_type &,
        const follow_list_type &
    );

    quix_messaging_lwd( const quix_messaging_lwd & ) = delete;

    quix_messaging_lwd( quix_messaging_lwd && ) = delete;

    quix_messaging_lwd &
    operator=( quix_messaging_lwd ) = delete;

    quix_messaging_lwd &
    operator=( quix_messaging_lwd && ) = delete;

    ~quix_messaging_lwd();

    bool
    aquire_test();

    event_type &
    aquire();

    void
    commit();

    bool
    reaquire_test();

    event_type &
    reaquire();

    void
    release();
};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
// OK if used in a multi process system where no process follows another on its own physical core
//#define BARRIER
//
// OK if used in a multi threaded system where no thread follows another in its own physical core
#define BARRIER asm volatile("": : :"memory")

//
// Needed when quix_nodes follow other quix_nodes that share physical cores
//#define BARRIER __sync_synchronize() // probably stronger than needed
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
struct zen::quix_messaging_lwd< E >::impl
{
    static constexpr int max_quix_node_count{ 8 };
    static constexpr int max_follower_count{ max_quix_node_count };
    static constexpr int pool_quix_messaging_slot_count{ 256 };
    static constexpr int pool_mask{ pool_quix_messaging_slot_count - 1 };

    using node_id_type =
    unsigned int;
    using follow_list_type =
    std::vector< unsigned int >;
    using event_type =
    E;

    struct data_type
    {
        zen::quix_structure_cacheline< data_type * > base_address;

        using meta_type  =
        zen::quix_structure_cacheline< uint64_t >[max_quix_node_count][2];
        meta_type meta_mem;

        using pool_type =
        zen::quix_structure_cacheline< event_type >[pool_quix_messaging_slot_count];
        pool_type pool_mem;
    };

    typename data_type::meta_type &meta_mem;
    typename data_type::pool_type &pool_mem;
    const node_id_type quix_node_id_mem;
    uint64_t *consumed_value_ptr[max_follower_count];

    impl(
        data_type *,
        const node_id_type &,
        const follow_list_type &
    );

    bool
    aquire_test();

    event_type &
    aquire();

    void
    commit();

    bool
    reaquire_test();

    event_type &
    reaquire();

    void
    release();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline
zen::quix_messaging_lwd< E >::impl::impl(
    data_type *data_arg,
    const node_id_type &quix_node_id_arg,
    const follow_list_type &follow_list_arg
)
    : meta_mem( data_arg->meta_mem )
    , pool_mem( data_arg->pool_mem )
    , quix_node_id_mem( quix_node_id_arg )
{
    if( data_arg->base_address.value == 0 )
        data_arg->base_address.value = data_arg;

    if( data_arg->base_address.value != data_arg )
        throw std::runtime_error( "Not all quix_messaging quix_nodes using memory at same base address" );

    if( follow_list_arg.size() >= max_follower_count )
        throw std::runtime_error( "To many followers" );

    int i = 0;
    for( auto followed_quix_node : follow_list_arg )
    {
        if(( followed_quix_node && followed_quix_node > max_quix_node_count ) || followed_quix_node == quix_node_id_mem )
            throw std::runtime_error( "Invalid follower id" );

        consumed_value_ptr[ i++ ] = &meta_mem[ followed_quix_node ][ 0 ].value;
    }
    consumed_value_ptr[ i++ ] = 0;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_lwd< E >::impl::aquire_test()
{
    uint64_t next_quix_messaging_slot = meta_mem[ quix_node_id_mem ][ 1 ] + 1 & pool_mask;
    uint64_t *volatile *walker = ( uint64_t *volatile * ) consumed_value_ptr;

    do
    {
        if( next_quix_messaging_slot == (( **walker ) & pool_mask ))
            return false;
    }
    while( *( ++walker ));

    return true;
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <thread>
#include <chrono>

template< typename E >
inline E &
zen::quix_messaging_lwd< E >::impl::aquire()
{
    uint64_t next_quix_messaging_slot = meta_mem[ quix_node_id_mem ][ 1 ].value + 1 & pool_mask;
    uint64_t *volatile *walker = ( uint64_t *volatile * ) consumed_value_ptr;

    do
    {
        while( next_quix_messaging_slot == (( **walker ) & pool_mask ))
            std::this_thread::yield();
    }
    while( *( ++walker ));

    uint64_t quix_node_quix_messaging_slot = meta_mem[ quix_node_id_mem ][ 1 ].value & pool_mask;
    ++meta_mem[ quix_node_id_mem ][ 1 ].value;
    return pool_mem[ quix_node_quix_messaging_slot ].value;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_lwd< E >::impl::commit()
{
    if( meta_mem[ quix_node_id_mem ][ 0 ].value == meta_mem[ quix_node_id_mem ][ 1 ].value )
        throw std::runtime_error( "commit called on event that was not aquired" );
    BARRIER;
    ++meta_mem[ quix_node_id_mem ][ 0 ].value;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_lwd< E >::impl::reaquire_test()
{
    uint64_t quix_node_quix_messaging_slot = meta_mem[ quix_node_id_mem ][ 1 ].value & pool_mask;
    uint64_t *volatile *walker = ( uint64_t *volatile * ) consumed_value_ptr;

    do
    {
        if( quix_node_quix_messaging_slot == (( **walker ) & pool_mask ))
            return false;
    }
    while( *( ++walker ));

    return true;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_lwd< E >::impl::reaquire()
{
    uint64_t quix_node_quix_messaging_slot = meta_mem[ quix_node_id_mem ][ 1 ].value & pool_mask;
    uint64_t *volatile *walker = ( uint64_t *volatile * ) consumed_value_ptr;

    do
    {
        while( quix_node_quix_messaging_slot == (( **walker ) & pool_mask ))
            std::this_thread::yield();
    }
    while( *( ++walker ));

    ++meta_mem[ quix_node_id_mem ][ 1 ].value;
    return pool_mem[ quix_node_quix_messaging_slot ].value;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_lwd< E >::impl::release()
{
    if( meta_mem[ quix_node_id_mem ][ 0 ].value == meta_mem[ quix_node_id_mem ][ 1 ].value )
        throw std::runtime_error( "release called on event that was not aquired" );
    BARRIER;
    ++meta_mem[ quix_node_id_mem ][ 0 ].value;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline
zen::quix_messaging_lwd< E >::quix_messaging_lwd(
    void *data_arg,
    const node_id_type &quix_node_id_arg,
    const follow_list_type &follow_list_arg
)
    : pimpl(
    new impl(
        reinterpret_cast< typename impl::data_type * >( data_arg ),
        quix_node_id_arg,
        follow_list_arg
    ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline
zen::quix_messaging_lwd< E >::~quix_messaging_lwd()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_lwd< E >::aquire_test()
{ return pimpl->aquire_test(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_lwd< E >::aquire()
{ return pimpl->aquire(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_lwd< E >::commit()
{ return pimpl->commit(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_lwd< E >::reaquire_test()
{ return pimpl->reaquire_test(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_lwd< E >::reaquire()
{ return pimpl->reaquire(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_lwd< E >::release()
{ return pimpl->release(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline std::string
to_string( const zen::quix_messaging_lwd< E > &quix_node_processor )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_TRANSPORT_LWD__HPP
