#ifndef __ZEN__BONES_FRAMEWORK__H
#define __ZEN__BONES_FRAMEWORK__H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace zen
{
    class bones_framework_dispatcher;

    using bones_framework_dispatcher_shared = types< bones_framework_dispatcher >::shared;

    class bones_framework_service;

    using bones_framework_service_shared = types< bones_framework_service >::shared;

    class bones_framework_directory;

    using bones_framework_directory_shared = types< bones_framework_directory >::shared;

    class bones_framework_session;

    using bones_framework_session_shared = types< bones_framework_session >::shared;

    class bones_framework_connection;

    using bones_framework_connection_shared = types< bones_framework_connection >::shared;

    class bones_framework_event;

    using bones_framework_event_shared = types< bones_framework_event >::shared;

    class bones_framework_acceptor;

    using bones_framework_acceptor_shared = types< bones_framework_acceptor >::shared;

    class bones_framework_accessor;

    using bones_framework_accessor_shared = types< bones_framework_accessor >::shared;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK__H
