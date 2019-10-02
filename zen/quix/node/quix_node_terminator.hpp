#ifndef __ZEN__QUIX_NODE_TERMINATOR__HPP
#define __ZEN__QUIX_NODE_TERMINATOR__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_node.h>
#include <zen/quix/utility/quix_utility_configuration.hpp>
#include <zen/quix/messaging/quix_messaging_slot.hpp> // TODO: because of auto deduction - refactor out
#include <iostream>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
class zen::quix_node_terminator
{
    struct impl;
    impl *pimpl;

    using transport_type =
    T;
    using quix_behaviour_type =
    B;

public:

    quix_node_terminator(
        transport_type &,
        quix_behaviour_type &
    );

    quix_node_terminator( const quix_node_terminator & ) = delete;

    quix_node_terminator( quix_node_terminator && ) = delete;

    quix_node_terminator &
    operator=( quix_node_terminator ) = delete;

    quix_node_terminator &
    operator=( quix_node_terminator && ) = delete;

    ~quix_node_terminator();

    void
    operator()();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
struct zen::quix_node_terminator<
    T,
    B
>::impl
{
    using transport_type =
    T;
    using quix_behaviour_type =
    B;

    transport_type &transport_mem;
    quix_behaviour_type &quix_behaviour_mem;

    impl(
        transport_type &,
        quix_behaviour_type &
    );

    void
    operator()();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
zen::quix_node_terminator<
    T,
    B
>::impl::impl(
    transport_type &transport_arg,
    quix_behaviour_type &quix_behaviour_arg
)
    : transport_mem( transport_arg )
    , quix_behaviour_mem( quix_behaviour_arg )
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
void
zen::quix_node_terminator<
    T,
    B
>::impl::operator()()
{
    std::cout
        << "Entering quix_node loop"
        << std::endl;
    do
    {
        auto quix_messaging_slot = zen::make_quix_messaging_reaquire_release_slot( transport_mem );
        quix_behaviour_mem( *quix_messaging_slot );
    }
    while( quix_behaviour_mem.post());
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
zen::quix_node_terminator<
    T,
    B
>::quix_node_terminator(
    transport_type &transport_arg,
    quix_behaviour_type &quix_behaviour_arg
)
    : pimpl(
    new impl(
        transport_arg,
        quix_behaviour_arg
    ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
zen::quix_node_terminator<
    T,
    B
>::~quix_node_terminator()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
void
zen::quix_node_terminator<
    T,
    B
>::operator()()
{ return pimpl->operator()(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B
>
std::string
to_string(
    const zen::quix_node_terminator<
        T,
        B
    > &quix_node_terminator
)
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_NODE_TERMINATOR__HPP
