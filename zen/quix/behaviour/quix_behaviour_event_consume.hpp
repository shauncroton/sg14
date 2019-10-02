#ifndef __ZEN__QUIX_BEHAVIOUR_EVENT_CONSUME__HPP
#define __ZEN__QUIX_BEHAVIOUR_EVENT_CONSUME__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_behaviour.h>
#include <stdexcept>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
class zen::quix_behaviour_event_consume
{
    struct impl;
    impl *pimpl;

public:

    using event_type = E;

    quix_behaviour_event_consume(
        void *,
        const unsigned int
    );

    quix_behaviour_event_consume( const quix_behaviour_event_consume & ) = delete;

    quix_behaviour_event_consume( quix_behaviour_event_consume && ) = delete;

    quix_behaviour_event_consume &
    operator=( quix_behaviour_event_consume ) = delete;

    quix_behaviour_event_consume &
    operator=( quix_behaviour_event_consume && ) = delete;

    ~quix_behaviour_event_consume();

    void
    operator()( event_type & );

    bool
    post();
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
struct zen::quix_behaviour_event_consume< E >::impl
{
    using event_type = E;

    unsigned int loops_mem{ 0 };

    impl( const unsigned int );

    void
    operator()( event_type & );

    bool
    post();
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_event_consume< E >::impl::impl(
    const unsigned int loops_arg
)
    : loops_mem( loops_arg )
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
void
zen::quix_behaviour_event_consume< E >::impl::operator()(
    event_type &event
)
{
    if( event != loops_mem )
        throw std::runtime_error( "Loops count mismatch" );
    event = 0;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
bool
zen::quix_behaviour_event_consume< E >::impl::post()
{
    return --loops_mem;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_event_consume< E >::quix_behaviour_event_consume(
    void *,
    const unsigned int loops_arg
)
    : pimpl( new impl( loops_arg ))
{
    return;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
zen::quix_behaviour_event_consume< E >::~quix_behaviour_event_consume()
{
    delete pimpl;
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
void
zen::quix_behaviour_event_consume< E >::operator()(
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
zen::quix_behaviour_event_consume< E >::post()
{
    return pimpl->post();
}

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename E >
std::string
to_string(
    const zen::quix_behaviour_event_consume< E > &quix_behaviour_event_consume_arg
)
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_BEHAVIOUR_EVENT_CONSUME__HPP
