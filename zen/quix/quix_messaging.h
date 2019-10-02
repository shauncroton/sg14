#ifndef __ZEN__QUIX_MESSAGING__H
#define __ZEN__QUIX_MESSAGING__H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace zen
{
    template< typename E >
    class quix_messaging_uni;

    template< typename E >
    class quix_messaging_dual;

    template< typename E >
    class quix_messaging_lwd;

    template< typename E >
    class quix_messaging_mcd;

    template< typename T, bool C >
    class quix_messaging_slot;

    template< typename T >
    auto
    make_quix_messaging_aquire_commit_slot( T &quix_messaging_arg );

    template< typename T >
    auto
    make_quix_messaging_reaquire_commit_slot( T &quix_messaging_arg );

    template< typename T >
    auto
    make_quix_messaging_aquire_release_slot( T &quix_messaging_arg );

    template< typename T >
    auto
    make_quix_messaging_reaquire_release_slot( T &quix_messaging_arg );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_MESSAGING__H
