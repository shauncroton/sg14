#ifndef __ZEN__QUIX_TRANSPORT_SLOT__HPP
#define __ZEN__QUIX_TRANSPORT_SLOT__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_messaging.h>
#include <stdexcept>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, bool C = true >
class zen::quix_messaging_slot
{
    using transport_type = T;
    using event_type = typename T::event_type;

    transport_type &transport_mem;
    event_type &value_mem;

public:

    using commit_quix_messaging_slot = quix_messaging_slot<
        transport_type,
        true
    >;
    using release_quix_messaging_slot = quix_messaging_slot<
        transport_type,
        false
    >;

    quix_messaging_slot(
        transport_type &transport_arg,
        event_type &value_arg
    );

    quix_messaging_slot( const quix_messaging_slot & ) = delete;

    quix_messaging_slot( quix_messaging_slot && ) = default;

    quix_messaging_slot &
    operator=( quix_messaging_slot ) = delete;

    quix_messaging_slot &
    operator=( quix_messaging_slot && ) = default;

    ~quix_messaging_slot();

    event_type &
    operator*();

    event_type *
    operator->();

};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, bool C >
zen::quix_messaging_slot<
    T,
    C
>::quix_messaging_slot(
    transport_type &transport_arg,
    event_type &value_arg
)
    : transport_mem( transport_arg )
    , value_mem( value_arg )
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, bool C >
zen::quix_messaging_slot<
    T,
    C
>::~quix_messaging_slot()
{
    if( C )
        transport_mem.commit();
    else
        transport_mem.release();
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, bool C >
auto
zen::quix_messaging_slot<
    T,
    C
>::operator*() -> event_type &
{
    return value_mem;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, bool C >
auto
zen::quix_messaging_slot<
    T,
    C
>::operator->() -> event_type *
{
    return &value_mem;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T >
auto
zen::make_quix_messaging_aquire_commit_slot( T &transport_arg )
{
    auto &value = transport_arg.aquire();
    return typename quix_messaging_slot< T >::commit_quix_messaging_slot(
        transport_arg,
        value
    );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T >
auto
zen::make_quix_messaging_reaquire_commit_slot( T &transport_arg )
{
    auto &value = transport_arg.reaquire();
    return typename quix_messaging_slot< T >::commit_quix_messaging_slot(
        transport_arg,
        value
    );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T >
auto
zen::make_quix_messaging_aquire_release_slot( T &transport_arg )
{
    auto &value = transport_arg.aquire();
    return typename quix_messaging_slot< T >::release_quix_messaging_slot(
        transport_arg,
        value
    );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T >
auto
zen::make_quix_messaging_reaquire_release_slot( T &transport_arg )
{
    auto &value = transport_arg.reaquire();
    return typename quix_messaging_slot< T >::release_quix_messaging_slot(
        transport_arg,
        value
    );
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, bool C >
std::string
to_string(
    const zen::quix_messaging_slot<
        T,
        C
    > &
)
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_TRANSPORT_SLOT__HPP
