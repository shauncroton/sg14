#ifndef __ZEN__BONES_FRAMEWORK_PROVIDER__HPP
#define __ZEN__BONES_FRAMEWORK_PROVIDER__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <zen/bones/framework/bones_framework_event.hpp>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename State >
class zen::bones_framework_provider
    : public zen::bones_framework_dispatcher
{
    bones_framework_provider( const bones_framework_provider & ) = delete;

    bones_framework_provider &
    operator=( bones_framework_provider ) = delete;

    bones_framework_provider( bones_framework_provider && ) = delete;

    bones_framework_provider &
    operator=( bones_framework_provider && ) = delete;

public:

    ~bones_framework_provider() = default;

    bones_framework_provider(
        const zen::bones_framework_directory_shared &directory_,
        const std::string &name_
    );

    using event_callback_function =
    std::function<
        void(
            zen::bones_framework_event &,
            State &
        )
    >;

    void
    invoke(
        event_callback_function &event_callback_,
        const zen::bones_framework_event_shared &enqueued_event_
    );

private:

    typename types< State >::shared _state;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename State >
zen::bones_framework_provider< State >::bones_framework_provider(
    const zen::bones_framework_directory_shared &directory_,
    const std::string &name_
)
    : zen::bones_framework_dispatcher(
    name_,
    directory_
)
    , _state( std::make_shared< State >())
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename State >
void
zen::bones_framework_provider< State >::invoke(
    event_callback_function &event_callback_,
    const zen::bones_framework_event_shared &enqueued_event_
)
{
    std::cout
        << "        enqueue: "
        << enqueued_event_->tag()
        << ", payload: "
        << enqueued_event_->payload()
        << " @ "
        << name()
        << std::endl;

    auto &state = _state;
    auto enqueued_callback = [
        state,
        &event_callback_
    ]( const zen::bones_framework_event_shared &event_ )
    {
        event_callback_(
            *event_,
            *state
        );
    };

    bones_framework_dispatcher::enqueue(
        {
            enqueued_event_,
            enqueued_callback
        }
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_PROVIDER__HPP
