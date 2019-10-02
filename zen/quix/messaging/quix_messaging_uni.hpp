#ifndef __ZEN__QUIX_TRANSPORT_UNI__HPP
#define __ZEN__QUIX_TRANSPORT_UNI__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_messaging.h>
#include <zen/quix/structure/quix_structure_cacheline.hpp>
#include <zen/quix/messaging/quix_messaging_slot.hpp>
#include <stdexcept>
#include <vector>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
class zen::quix_messaging_uni
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

    quix_messaging_uni(
        void *,
        const node_id_type &,
        const follow_list_type &
    );

    quix_messaging_uni( const quix_messaging_uni & ) = delete;

    quix_messaging_uni( quix_messaging_uni && ) = delete;

    quix_messaging_uni &
    operator=( quix_messaging_uni ) = delete;

    quix_messaging_uni &
    operator=( quix_messaging_uni && ) = delete;

    ~quix_messaging_uni();

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
struct zen::quix_messaging_uni< E >::impl
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
        zen::quix_structure_cacheline< event_type * >[max_quix_node_count];
        meta_type meta_mem;

        using pool_type =
        zen::quix_structure_cacheline< event_type >[pool_quix_messaging_slot_count];
        pool_type pool_mem;
    };

    typename data_type::meta_type &meta_mem;
    typename data_type::pool_type &pool_mem;
    const node_id_type quix_node_id_mem;
    unsigned int pool_index{ 0 };
    event_type *pending_value_ptr{ nullptr };
    event_type *volatile *consumed_value_ptr{ nullptr };

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
#include <iostream>

template< typename E >
inline
zen::quix_messaging_uni< E >::impl::impl(
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

    if( follow_list_arg.size() > max_follower_count )
        throw std::logic_error( "To many followers" );

    int f = *follow_list_arg.begin();
    consumed_value_ptr = &meta_mem[ f ].value;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_uni< E >::impl::aquire_test()
{
    if( pending_value_ptr )
        throw std::logic_error( "aquire_test called out of sequence" );

    return meta_mem[ quix_node_id_mem ].value
        ? false
        : true;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_uni< E >::impl::aquire()
{
    if( pending_value_ptr )
        throw std::logic_error( "aquire called out of sequence" );

    while( aquire_test() == false );
    pending_value_ptr = &pool_mem[ ++pool_index & pool_mask ].value;
    return *pending_value_ptr;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_uni< E >::impl::commit()
{
    if( !pending_value_ptr )
        throw std::logic_error( "commit called out of sequence" );

    while( meta_mem[ quix_node_id_mem ].value );
    BARRIER;
    meta_mem[ quix_node_id_mem ].value = pending_value_ptr;
    pending_value_ptr = nullptr;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_uni< E >::impl::reaquire_test()
{
    if( pending_value_ptr )
        throw std::logic_error( "reaquire_test called out of sequence" );

    return *consumed_value_ptr
        ? true
        : false;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_uni< E >::impl::reaquire()
{
    if( pending_value_ptr )
        throw std::logic_error( "reaquire called out of sequence" );

    while( reaquire_test() == false );
    pending_value_ptr = *consumed_value_ptr;
    *consumed_value_ptr = 0;
    return *pending_value_ptr;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_uni< E >::impl::release()
{
    if( !pending_value_ptr )
        throw std::logic_error( "release called out of sequence" );

    pending_value_ptr = nullptr;
    return;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline
zen::quix_messaging_uni< E >::quix_messaging_uni(
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
zen::quix_messaging_uni< E >::~quix_messaging_uni()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_uni< E >::aquire_test()
{ return pimpl->aquire_test(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_uni< E >::aquire()
{ return pimpl->aquire(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_uni< E >::commit()
{ return pimpl->commit(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline bool
zen::quix_messaging_uni< E >::reaquire_test()
{ return pimpl->reaquire_test(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline E &
zen::quix_messaging_uni< E >::reaquire()
{ return pimpl->reaquire(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline void
zen::quix_messaging_uni< E >::release()
{ return pimpl->release(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
inline std::string
to_string( const zen::quix_messaging_uni< E > &quix_node_processor )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_TRANSPORT_UNI__HPP
