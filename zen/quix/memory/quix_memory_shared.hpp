///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#ifndef __ZEN__QUIX_MEMORY_SHARED__HPP
#define __ZEN__QUIX_MEMORY_SHARED__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_memory.h>
#include <cstddef>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::quix_memory_shared
{
    struct impl;
    impl *pimpl;

public:

    quix_memory_shared(
        const std::size_t,
        const std::size_t
    );

    quix_memory_shared( const quix_memory_shared & ) = delete;

    quix_memory_shared( quix_memory_shared && ) = delete;

    quix_memory_shared &
    operator=( quix_memory_shared ) = delete;

    quix_memory_shared &
    operator=( quix_memory_shared && ) = delete;

    ~quix_memory_shared();

    void *
    data(
        const std::size_t = 0
    );

    std::size_t
    size(
        const std::size_t = 0
    );
};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_MEMORY_SHARED__HPP
