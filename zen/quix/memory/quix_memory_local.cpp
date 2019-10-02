///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/memory/quix_memory_local.hpp>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <stdexcept>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct zen::quix_memory_local::impl
{
    void *unaligned_data_mem{ nullptr };
    void *data_mem{ nullptr };
    std::size_t size_mem{ 0 };

    impl( const std::size_t size_arg );

    ~impl();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_local::impl::impl( const std::size_t size_arg )
    : unaligned_data_mem( malloc( size_arg + 63 ))
    , data_mem( unaligned_data_mem )
    , size_mem( size_arg )
{
    std::size_t space = size_arg + 63;

    if( !std::align(
        64,
        size_arg,
        data_mem,
        space
    ))
        throw std::runtime_error( "Failed to align allocated memory on cache boundry" );

    if( space < size_arg )
        throw std::runtime_error( "Not enough space left after alignement" );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_local::impl::~impl()
{ free( unaligned_data_mem ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_local::quix_memory_local( const std::size_t size_arg )
    : pimpl( new impl( size_arg ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_local::~quix_memory_local()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void *
zen::quix_memory_local::data( const std::size_t offset_arg )
{ return reinterpret_cast< uint8_t * >( pimpl->data_mem ) + offset_arg; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::size_t
zen::quix_memory_local::size( const std::size_t offset_arg )
{ return pimpl->size_mem - offset_arg; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
to_string( const zen::quix_memory_local &quix_memory_local_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
