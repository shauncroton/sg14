#ifndef __ZEN__QUIX_NETWORK_SHARED_LISTENER__HPP
#define __ZEN__QUIX_NETWORK_SHARED_LISTENER__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_network.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::quix_network_shared_listener
{
    struct impl;
    impl *pimpl;

public:

    quix_network_shared_listener(
        const std::string &,
        const std::string &,
        const std::string &
    );

    quix_network_shared_listener( const quix_network_shared_listener & ) = delete;

    quix_network_shared_listener( quix_network_shared_listener && ) = delete;

    quix_network_shared_listener &
    operator=( quix_network_shared_listener ) = delete;

    quix_network_shared_listener &
    operator=( quix_network_shared_listener && ) = delete;

    ~quix_network_shared_listener();

    void
    operator()();
};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_NETWORK_SHARED_LISTENER__HPP
