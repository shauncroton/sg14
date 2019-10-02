///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#ifndef __ZEN__QUIX_NODE_PROCESSOR__HPP
#define __ZEN__QUIX_NODE_PROCESSOR__HPP
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
    typename B,
    typename J
>
class zen::quix_node_processor
{
    struct impl;
    impl *pimpl;

    using transport_type =
    T;
    using journal_type =
    J;
    using quix_behaviour_type =
    B;

public:

    quix_node_processor(
        transport_type &,
        quix_behaviour_type &,
        journal_type &
    );

    quix_node_processor( const quix_node_processor & ) = delete;

    quix_node_processor( quix_node_processor && ) = delete;

    quix_node_processor &
    operator=( quix_node_processor ) = delete;

    quix_node_processor &
    operator=( quix_node_processor && ) = delete;

    ~quix_node_processor();

    void
    operator()();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
struct zen::quix_node_processor<
    T,
    B,
    J
>::impl
{
    using transport_type =
    T;
    using quix_behaviour_type =
    B;
    using journal_type =
    J;

    transport_type &transport_mem;
    quix_behaviour_type &quix_behaviour_mem;
    journal_type &journal_mem;

    impl(
        transport_type &,
        quix_behaviour_type &,
        journal_type &
    );

    void
    operator()();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
zen::quix_node_processor<
    T,
    B,
    J
>::impl::impl(
    transport_type &transport_arg,
    quix_behaviour_type &quix_behaviour_arg,
    journal_type &journal_arg
)
    : transport_mem( transport_arg )
    , quix_behaviour_mem( quix_behaviour_arg )
    , journal_mem( journal_arg )
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
void
zen::quix_node_processor<
    T,
    B,
    J
>::impl::operator()()
{
    std::cout
        << "Entering quix_node loop"
        << std::endl;
    do
    {
        auto quix_messaging_slot = zen::make_quix_messaging_reaquire_commit_slot( transport_mem );
        quix_behaviour_mem(
            *quix_messaging_slot,
            journal_mem
        );
        journal_type::commit( journal_mem );
    }
    while( quix_behaviour_mem.post());
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
zen::quix_node_processor<
    T,
    B,
    J
>::quix_node_processor(
    transport_type &transport_arg,
    quix_behaviour_type &quix_behaviour_arg,
    journal_type &journal_arg
)
    : pimpl(
    new impl(
        transport_arg,
        quix_behaviour_arg,
        journal_arg
    ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
zen::quix_node_processor<
    T,
    B,
    J
>::~quix_node_processor()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
void
zen::quix_node_processor<
    T,
    B,
    J
>::operator()()
{ return pimpl->operator()(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename T,
    typename B,
    typename J
>
std::string
to_string(
    const zen::quix_node_processor<
        T,
        J,
        B
    > &quix_node_processor
)
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_NODE_PROCESSOR__HPP
