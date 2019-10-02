#ifndef __ZEN__QUIX_MEMORY_MAPPED__HPP
#define __ZEN__QUIX_MEMORY_MAPPED__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_memory.h>
#include <cstddef>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
class zen::quix_memory_mapped
{
    struct impl;
    impl *pimpl;

public:

    quix_memory_mapped(
        const std::string &,
        const std::size_t,
        const std::size_t,
        const bool = false
    );

    quix_memory_mapped( const quix_memory_mapped & ) = delete;

    quix_memory_mapped( quix_memory_mapped && ) = delete;

    quix_memory_mapped &
    operator=( quix_memory_mapped ) = delete;

    quix_memory_mapped &
    operator=( quix_memory_mapped && ) = delete;

    ~quix_memory_mapped();

    void *
    data( const std::size_t = 0 );

    std::size_t
    size( const std::size_t = 0 );
};
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_MEMORY_MAPPED__HPP
