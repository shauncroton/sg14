#ifndef __ZEN__BONES_FRAMEWORK_DISPATCHER__HPP
#define __ZEN__BONES_FRAMEWORK_DISPATCHER__HPP

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
class zen::bones_framework_dispatcher
{
    bones_framework_dispatcher( const bones_framework_dispatcher & ) = delete;

    bones_framework_dispatcher &
    operator=( bones_framework_dispatcher ) = delete;

    bones_framework_dispatcher( bones_framework_dispatcher && ) = delete;

    bones_framework_dispatcher &
    operator=( bones_framework_dispatcher && ) = delete;

protected:

    virtual ~bones_framework_dispatcher();

    bones_framework_dispatcher(
        std::string name_,
        zen::bones_framework_directory_shared directory_
    );

    using enqueued_callback_function =
    std::function< void( zen::bones_framework_event_shared & ) >;

    using queue_content =
    std::pair<
        enqueued_callback_function,
        zen::bones_framework_event_shared
    >;

    void
    enqueue(
        enqueued_callback_function &enqueued_callback_,
        const zen::bones_framework_event_shared &enqueued_event_
    );

public:

    const std::string &
    name() const
    { return _name; }

    const zen::bones_framework_directory_shared &
    directory()
    { return _directory; }

private:

    void
    process( std::promise< void > start_thread );

      const std::string _name;
    const zen::bones_framework_directory_shared _directory;
    std::thread _processing_thread;
    std::mutex _processing_queue_mutex;
    std::queue< queue_content > _processing_queue;
    std::condition_variable _processing_queue_condition_variable;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_DISPATCHER__HPP
