#ifndef __ZEN__QUIX_BEHAVIOUR_EVENT_PUBLISH__HPP
#define __ZEN__QUIX_BEHAVIOUR_EVENT_PUBLISH__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_behaviour.h>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
class zen::quix_behaviour_event_publish
{
    struct impl;
    impl *pimpl;

public:

    using event_type =
    E;

    quix_behaviour_event_publish(
        void *,
        const unsigned int
    );

    quix_behaviour_event_publish( const quix_behaviour_event_publish & ) = delete;

    quix_behaviour_event_publish( quix_behaviour_event_publish && ) = delete;

    quix_behaviour_event_publish &
    operator=( quix_behaviour_event_publish ) = delete;

    quix_behaviour_event_publish &
    operator=( quix_behaviour_event_publish && ) = delete;

    ~quix_behaviour_event_publish();

    void
    operator()( event_type & );

    bool
    post();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
struct zen::quix_behaviour_event_publish< E >::impl
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
zen::quix_behaviour_event_publish< E >::impl::impl( const unsigned int loops_arg )
    : loops_mem( loops_arg )
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
void
zen::quix_behaviour_event_publish< E >::impl::operator()( event_type &event )
{ event = loops_mem; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
bool
zen::quix_behaviour_event_publish< E >::impl::post()
{ return --loops_mem; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_event_publish< E >::quix_behaviour_event_publish(
    void *,
    const unsigned int loops
)
    : pimpl( new impl( loops ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_event_publish< E >::~quix_behaviour_event_publish()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
void
zen::quix_behaviour_event_publish< E >::operator()( event_type &event )
{ return pimpl->operator()( event ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
bool
zen::quix_behaviour_event_publish< E >::post()
{ return pimpl->post(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
std::string
to_string( const zen::quix_behaviour_event_publish< E > &quix_behaviour_event_publish_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_BEHAVIOUR_EVENT_PUBLISH__HPP
