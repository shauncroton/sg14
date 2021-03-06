///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/framework/bones_framework_event.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_event::bones_framework_event(
    std::string tag_,
    std::string payload_
)
    : _event_tag( std::move( tag_ ))
    , _event_payload( std::move( payload_ ))
{}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
