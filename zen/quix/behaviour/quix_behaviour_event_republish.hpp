#ifndef __ZEN__QUIX_BEHAVIOUR_EVENT_REPUBLISH__HPP
#define __ZEN__QUIX_BEHAVIOUR_EVENT_REPUBLISH__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_behaviour.h>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
class zen::quix_behaviour_event_republish
{
    struct impl;
    impl *pimpl;

public:

    using event_type =
    E;

    quix_behaviour_event_republish(
        void *,
        const unsigned int
    );

    quix_behaviour_event_republish( const quix_behaviour_event_republish & ) = delete;

    quix_behaviour_event_republish( quix_behaviour_event_republish && ) = delete;

    quix_behaviour_event_republish &
    operator=( quix_behaviour_event_republish ) = delete;

    quix_behaviour_event_republish &
    operator=( quix_behaviour_event_republish && ) = delete;

    ~quix_behaviour_event_republish();

    void
    operator()( event_type & );

    bool
    post();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
struct zen::quix_behaviour_event_republish< E >::impl
{
    using event_type =
    E;

    unsigned int loops_mem{ 0 };

    impl( const unsigned int );

    void
    operator()( event_type & );

    bool
    post();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_event_republish< E >::impl::impl( const unsigned int loops_arg )
    : loops_mem( loops_arg )
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
void
zen::quix_behaviour_event_republish< E >::impl::operator()( event_type &event )
{
    if( event != loops_mem )
        throw std::runtime_error( "Loops count mismatch" );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
bool
zen::quix_behaviour_event_republish< E >::impl::post()
{ return --loops_mem; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_event_republish< E >::quix_behaviour_event_republish(
    void *,
    const unsigned int loops
)
    : pimpl( new impl( loops ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_event_republish< E >::~quix_behaviour_event_republish()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
void
zen::quix_behaviour_event_republish< E >::operator()( event_type &event )
{ return pimpl->operator()( event ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
bool
zen::quix_behaviour_event_republish< E >::post()
{ return pimpl->post(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
std::string
to_string( const zen::quix_behaviour_event_republish< E > &quix_behaviour_event_republish_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_BEHAVIOUR_EVENT_REPUBLISH__HPP
