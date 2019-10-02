///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/memory/quix_memory_mapped.hpp>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct zen::quix_memory_mapped::impl
{
    void *data_mem{ nullptr };
    std::size_t size_mem{ 0 };

    impl(
        const std::string &,
        const std::size_t,
        const std::size_t,
        const bool
    );

    ~impl();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_mapped::impl::impl(
    const std::string &filename_arg,
    const std::size_t base_arg,
    const std::size_t size_arg,
    const bool create_arg
)
    : size_mem( size_arg )
{
    if( create_arg )
    {
        std::ofstream transport_file(
            filename_arg,
            std::ios::binary
        );

        for(
            int i = 0;
            i < size_arg;
            ++i )
            transport_file.put( 0 );
    }

    int fd = open(
        filename_arg.c_str(),
        O_RDWR,
        0
    );
    if( fd < 0 )
        throw std::runtime_error( "Failed to open file to memory map" );

    data_mem = mmap(( void * ) ( base_arg * 1024 ),
        size_arg,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );
    close( fd );

    if( uint64_t( data_mem ) < 0 )
        throw std::runtime_error( "Failed to map file into memory" );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_mapped::impl::~impl()
{
    munmap(
        data_mem,
        size_mem
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_mapped::quix_memory_mapped(
    const std::string &filename_arg,
    const std::size_t base_arg,
    const std::size_t size_arg,
    const bool create_arg
)
    : pimpl(
    new impl(
        filename_arg,
        base_arg,
        size_arg,
        create_arg
    ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_memory_mapped::~quix_memory_mapped()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void *
zen::quix_memory_mapped::data( const std::size_t offset_arg )
{ return reinterpret_cast< uint8_t * >( pimpl->data_mem ) + offset_arg; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::size_t
zen::quix_memory_mapped::size( const std::size_t offset_arg )
{ return pimpl->size_mem - offset_arg; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
to_string( const zen::quix_memory_mapped &quix_memory_mapped_arg )
{
    throw std::runtime_error( "Unimplemented" );
    return "";
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
