#ifndef __ZEN__BONES_FRAMEWORK_EVENT__HPP
#define __ZEN__BONES_FRAMEWORK_EVENT__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <unordered_map>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::bones_framework_event
{
    bones_framework_event( const bones_framework_event & ) = delete;

    bones_framework_event &
    operator=( bones_framework_event ) = delete;

    bones_framework_event( bones_framework_event && ) = delete;

    bones_framework_event &
    operator=( bones_framework_event && ) = delete;

public:

    ~bones_framework_event() = default;

    bones_framework_event(
        std::string tag_,
        std::string payload_
    );

    const std::string &
    tag() const
    {
        return _event_tag;
    }

    const std::string &
    payload()
    {
        return _event_payload;
    }

private:

    const std::string _event_tag;
    const std::string _event_payload;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_EVENT__HPP