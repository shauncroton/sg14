#ifndef __ZEN__BONES_FRAMEWORK_SESSION__HPP
#define __ZEN__BONES_FRAMEWORK_SESSION__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <zen/bones/framework/bones_framework_accessor.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::bones_framework_session
{
    bones_framework_session( const bones_framework_session & ) = delete;

    bones_framework_session &
    operator=( bones_framework_session ) = delete;

    bones_framework_session( bones_framework_session && ) = delete;

    bones_framework_session &
    operator=( bones_framework_session && ) = delete;

public:

    ~bones_framework_session();

    bones_framework_session(
        zen::bones_framework_dispatcher_shared session_dispatcher_,
        std::string name_,
        zen::bones_framework_accessor_shared session_accessor_
    );

    const std::string &
    name()
    { return _name; }

    zen::bones_framework_dispatcher_shared &
    dispatcher()
    { return _session_dispatcher; }

    zen::bones_framework_accessor_shared
    accessor()
    { return _session_accessor.lock(); }

    void
    accessor_dispatch( const zen::bones_framework_event_shared &event_ );

    void
    accessor_dispatch(
        const std::string &tag_,
        const std::string &payload_
    );

    template< typename Session >
    void
    accessor_callback(
        const std::string &name_,
        void (Session::*callback_function_)( const zen::bones_framework_event_shared &event_ ),
        Session *callback_session_
    );

public:

private:

    std::string _name;
    types< zen::bones_framework_accessor >::weak _session_accessor;
    zen::bones_framework_dispatcher_shared _session_dispatcher{ nullptr };
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename Session
>
void
zen::bones_framework_session::accessor_callback(
    const std::string &name_,
    void (Session::*callback_function_)( const zen::bones_framework_event_shared &event_ ),
    Session *callback_session_
)
{
    auto session_accessor = _session_accessor.lock();
    if( session_accessor )
    {
        session_accessor->callback(
            name_,
            callback_function_,
            callback_session_
        );
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_SESSION__HPP
