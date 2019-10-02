#ifndef __ZEN__QUIX_STRUCTURE_BUFFER__HPP
#define __ZEN__QUIX_STRUCTURE_BUFFER__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_structure.h>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T, std::size_t R = 0 >
struct alignas( 64 ) zen::quix_structure_buffer
{
    using type = T;
    static constexpr std::size_t reserved = R;

    std::size_t size;
    type data[reserved];
};

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_STRUCTURE_BUFFER__HPP