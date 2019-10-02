///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/framework/bones_framework_session.hpp>
#include <zen/bones/framework/bones_framework_dispatcher.hpp>
#include <zen/bones/framework/bones_framework_event.hpp>
#include <zen/bones/framework/bones_framework_accessor.hpp>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_session::bones_framework_session(
    zen::bones_framework_dispatcher_shared session_dispatcher_,
    std::string name_,
    zen::bones_framework_accessor_shared session_accessor_
)
    : _name( std::move( name_ ))
    , _session_dispatcher( std::move( session_dispatcher_ ))
    , _session_accessor( std::move( session_accessor_ ))
{
    std::cout << "session " << _name << " is created" << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_session::~bones_framework_session()
{
    std::cout << "session " << _name << " is destroyed" << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_dispatcher_shared &
zen::bones_framework_session::get_dispatcher()
{
    return _session_dispatcher;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor_shared
zen::bones_framework_session::get_accessor()
{
    return _session_accessor.lock();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_session::accessor_dispatch(
    const std::string tag_,
    const std::string payload_
)
{
    auto session_accessor = _session_accessor.lock();
    if( session_accessor )
    {
        session_accessor->dispatch(
            tag_,
            payload_
        );
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_session::accessor_dispatch(
    const zen::bones_framework_event_shared &event_
)
{
    auto session_accessor = _session_accessor.lock();
    if( session_accessor )
    {
        session_accessor->dispatch(
            event_
        );
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
