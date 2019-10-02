#ifndef __ZEN__QUIX_BEHAVIOUR_BASE__HPP
#define __ZEN__QUIX_BEHAVIOUR_BASE__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_behaviour.h>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
class zen::quix_behaviour_base
{
    struct impl;
    impl *pimpl;

public:

    using event_type =
    E;

    quix_behaviour_base( void * );

    quix_behaviour_base( const quix_behaviour_base & ) = delete;

    quix_behaviour_base( quix_behaviour_base && ) = delete;

    quix_behaviour_base &
    operator=( quix_behaviour_base ) = delete;

    quix_behaviour_base &
    operator=( quix_behaviour_base && ) = delete;

    ~quix_behaviour_base();

    void
    operator()( event_type & );

    void
    post();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
struct zen::quix_behaviour_base< E >::impl
{
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_base< E >::quix_behaviour_base( void * )
    : pimpl( new impl )
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_base< E >::~quix_behaviour_base()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
std::string
to_string( const zen::quix_behaviour_base< E > &quix_quix_behaviour_base_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_BEHAVIOUR_BASE__HPP

#if 0
#ifndef ____ZEN__QUIX_QUIX_BEHAVIOUR_BASE_H__
#define ____ZEN__QUIX_QUIX_BEHAVIOUR_BASE_H__


#include <config.h>
#include <stdint.h> // uint64_t
#include <stdlib.h> //size_t


// Forward declarations
struct buffer;
struct event;
struct order;


// Raw data buffer quix_structure
typedef struct buffer
{ size_t size;
  char data[0];}
buffer_t;
char* buffer_to_string( buffer_t *buffer_ptr );


// Event Structure
typedef struct event
{ int id;
  int type;
  double price;
  double quanity;
  struct event *orig_ord_ptr;
  struct order *order_ptr;}
event_t;
char* event_to_string( event_t *event_ptr );


// Order struture
typedef struct order
{ int value;
  struct event *event_ptr;}
order_t;
char* order_to_string( order_t *order_ptr );


// Behavior required functions
void* init_quix_behaviour_base( void* raw );
uint64_t *exec_quix_behaviour_base( uint64_t *event_ptr );
void post_quix_behaviour_base();


#endif // ____ZEN__QUIX_QUIX_BEHAVIOUR_BASE_H__
#endif
