#ifndef __ZEN__QUIX_STRUCTURE_CACHELINE__HPP
#define __ZEN__QUIX_STRUCTURE_CACHELINE__HPP
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/quix_structure.h>

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
template< typename T >
struct alignas(64) zen::quix_structure_cacheline
{
    using type = T;
    type value;
};
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif // __ZEN__QUIX_STRUCTURE_CACHELINE__HPP
