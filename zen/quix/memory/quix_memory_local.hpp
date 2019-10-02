#ifndef __ZEN__QUIX_MEMORY_LOCAL__HPP
#define __ZEN__QUIX_MEMORY_LOCAL__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_memory.h>
#include <cstddef>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
class zen::quix_memory_local
{
    struct impl;
    impl *pimpl;

public:

    quix_memory_local( const std::size_t );

    quix_memory_local( const quix_memory_local & );

    quix_memory_local( quix_memory_local && );

    quix_memory_local &
    operator=( quix_memory_local );

    quix_memory_local &
    operator=( quix_memory_local && );

    ~quix_memory_local();

    void *
    data( const std::size_t = 0 );

    std::size_t
    size( const std::size_t = 0 );
};
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_MEMORY_LOCAL__HPP
