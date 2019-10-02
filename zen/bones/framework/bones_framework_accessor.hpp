#ifndef __ZEN__BONES_FRAMEWORK_ACCESSOR__HPP
#define __ZEN__BONES_FRAMEWORK_ACCESSOR__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <zen/bones/framework/bones_framework_dispatcher.hpp>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::bones_framework_accessor
    : public std::enable_shared_from_this< zen::bones_framework_accessor >
{
    using entangled_shared =
    types< zen::bones_framework_accessor >::weak;

    using event_callback_function =
    std::function<
        void( zen::bones_framework_event_shared & )
    >;

    using callbacks_type =
    std::unordered_map<
        std::string,
        event_callback_function
    >;

    bones_framework_accessor( const zen::bones_framework_accessor & ) = delete;

    bones_framework_accessor &
    operator=( zen::bones_framework_accessor ) = delete;

    bones_framework_accessor( zen::bones_framework_accessor && ) = delete;

    bones_framework_accessor &
    operator=( zen::bones_framework_accessor && ) = delete;

public:

    ~bones_framework_accessor();

    bones_framework_accessor(
        zen::bones_framework_dispatcher_shared dispatcher_,
        std::string name_,
        zen::bones_framework_accessor_shared ownership_
    );

    bones_framework_accessor(
        const zen::bones_framework_dispatcher_shared &dispatcher_,
        const std::string &name_
    );

    static zen::bones_framework_accessor_shared
    factory(
        zen::bones_framework_dispatcher_shared dispatcher_,
        const std::string &name_
    );

    static zen::bones_framework_accessor_shared
    factory(
        zen::bones_framework_dispatcher_shared dispatcher_,
        const std::string &host_,
        int port_
    );

    void
    start_dispatcher(
        zen::bones_framework_accessor_shared me_shared_,
        int sock_fd_
    );

    void
    set_entangled( zen::bones_framework_accessor_shared &entangled_ );

    void
    set_session_ownership( zen::bones_framework_session_shared &session_instance_ );

    template<
        typename Session
    >
    void
    callback(
        const std::string &name_,
        void (Session::*callback_function_)( const zen::bones_framework_event_shared &event_ ),
        Session *callback_session_
    );

    void
    uncallback( const std::string &name_ );

    void
    deliver( const zen::bones_framework_event_shared &event_ );

    void
    dispatch( const zen::bones_framework_event_shared &event_ );

    void
    dispatch(
        const std::string &tag_,
        const std::string &payload_ = ""
    );

private:

    void
    dispatcher(
        zen::bones_framework_accessor_shared keep_me_alive_,
        int sock_fd_
    );

private:

    int _sock_fd{ -1 };
    std::string _name;
    entangled_shared _entangled;
    callbacks_type _callbacks;
    zen::bones_framework_dispatcher_shared _service_dispatcher{ nullptr };
    zen::bones_framework_accessor_shared _accessor_ownership{ nullptr };
    zen::bones_framework_session_shared _session_ownership{ nullptr };
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename Session
>
void
zen::bones_framework_accessor::callback(
    const std::string &name_,
    void (Session::*callback_function_)( const zen::bones_framework_event_shared &event_ ),
    Session *callback_session_
)
{
    auto callback = [
        callback_session_,
        callback_function_
    ]( zen::bones_framework_event_shared &event_ )
    { ( callback_session_->*callback_function_ )( event_ ); };

    _callbacks[ name_ ] = callback;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_ACCESSOR__HPP
