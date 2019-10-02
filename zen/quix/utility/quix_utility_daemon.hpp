#ifndef __ZEN__QUIX_UTILITY_DAEMON__HPP
#define __ZEN__QUIX_UTILITY_DAEMON__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_utility.h>

//#include <zen/quix/node/quix_node.h>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::quix_utility_daemon
{
    struct impl;
    impl *pimpl;

public:

    //  quix_utility_daemon( zen::quix_node_quix_node& );

    quix_utility_daemon( const quix_utility_daemon & );

    quix_utility_daemon( quix_utility_daemon && );

    quix_utility_daemon &
    operator=( quix_utility_daemon );

    quix_utility_daemon &
    operator=( quix_utility_daemon && );

    ~quix_utility_daemon();
};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_UTILITY_DAEMON__HPP
