#ifndef __ZEN__QUIX_BEHAVIOUR_FILE_WRITE__HPP
#define __ZEN__QUIX_BEHAVIOUR_FILE_WRITE__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_behaviour.h>
#include <zen/quix/structure/quix_structure_buffer.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
class zen::quix_behaviour_file_write
{
    struct impl;
    impl *pimpl;

public:

    using event_type =
    E;

    quix_behaviour_file_write( const std::string & );

    quix_behaviour_file_write( const quix_behaviour_file_write & ) = delete;

    quix_behaviour_file_write( quix_behaviour_file_write && ) = delete;

    quix_behaviour_file_write &
    operator=( quix_behaviour_file_write ) = delete;

    quix_behaviour_file_write &
    operator=( quix_behaviour_file_write && ) = delete;

    ~quix_behaviour_file_write();

    void
    operator()( event_type & );

    bool
    post();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
struct zen::quix_behaviour_file_write< E >::impl
{
    using event_type =
    E;

    std::ofstream file;
    bool again_mem{ true };

    impl( const std::string & );

    void
    operator()( event_type & );

    bool
    post();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_file_write< E >::impl::impl( const std::string &filename_arg )
    : file( filename_arg )
{ file.exceptions( std::ifstream::badbit | std::ifstream::failbit ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
void
zen::quix_behaviour_file_write< E >::impl::operator()( event_type &event )
{
    if( event.buffer_mem->size )
    {
        std::cout
            << "\""
            << std::string(
                event.buffer_mem->data,
                event.buffer_mem->size
            )
            << "\"\n";
        file.write(
            event.buffer_mem->data,
            event.buffer_mem->size
        );
        file.put( '\n' );
    }
    else
        again_mem = false;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
bool
zen::quix_behaviour_file_write< E >::impl::post()
{ return again_mem; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_file_write< E >::quix_behaviour_file_write( const std::string &filename_arg )
    : pimpl( new impl( filename_arg ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
zen::quix_behaviour_file_write< E >::~quix_behaviour_file_write()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
void
zen::quix_behaviour_file_write< E >::operator()( event_type &event )
{ return pimpl->operator()( event ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
bool
zen::quix_behaviour_file_write< E >::post()
{ return pimpl->post(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename E >
std::string
to_string( const zen::quix_behaviour_file_write< E > &quix_behaviour_file_write_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_BEHAVIOUR_FILE_WRITE__HPP
