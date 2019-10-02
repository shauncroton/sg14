///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/framework/bones_framework_dispatcher.hpp>
#include <zen/bones/framework/bones_framework_event.hpp>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///

zen::bones_framework_dispatcher::bones_framework_dispatcher(
    std::string name_,
    zen::bones_framework_directory_shared directory_
)
    : _name( std::move( name_ ))
    , _directory( std::move( directory_ ))
{
    std::promise< void > start_thread;
    auto thread_started = start_thread.get_future();
    _processing_thread = std::thread(
        &zen::bones_framework_dispatcher::process_events,
        this,
        std::move( start_thread ));
    thread_started.get();

    std::cout << "bones_framework_dispatcher " << _name << " is created" << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///

zen::bones_framework_dispatcher::~bones_framework_dispatcher()
{
    {
        std::lock_guard< std::mutex > g( _processing_queue_mutex );
        _processing_queue.emplace(
            [](
                zen::bones_framework_event_shared &
            )
            {
            },
            nullptr
        );
    }
    _processing_queue_condition_variable.notify_one();
    _processing_thread.join();

    std::cout << "bones_framework_dispatcher " << _name << " is destroyed" << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_dispatcher::enqueue(
    event_callback_function &event_callback_,
    const zen::bones_framework_event_shared &enqueued_event_
)
{
    std::cout << "        enqueue: " << enqueued_event_->tag() << ", payload: " << enqueued_event_->payload() << " @ " << get_name() << std::endl;

    {
        std::lock_guard< std::mutex > g( _processing_queue_mutex );
        _processing_queue.emplace(
            event_callback_,
            enqueued_event_
        );
    }
    _processing_queue_condition_variable.notify_one();
    std::this_thread::sleep_for( 1ms );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_dispatcher::process_events(
    std::promise< void > start_thread
)
{
    std::cout << "bones_framework_dispatcher " << _name << " thread is starting...." << std::endl;
    start_thread.set_value();
    while( true )
    {
        //std::cout << "bones_framework_dispatcher " << name << " thread is waiting...." << std::endl;
        std::unique_lock< std::mutex > lock( _processing_queue_mutex );
        if( _processing_queue.empty())
        {
            _processing_queue_condition_variable.wait( lock );
        }
        //std::cout << "bones_framework_dispatcher " << name << " thread is working...." << std::endl;
        if( _processing_queue.empty())
        {
            continue;
        }
        auto event_callback = _processing_queue.front().first;
        auto enqueued_event = _processing_queue.front().second;
        _processing_queue.pop();
        lock.unlock();
        if( !enqueued_event )
        {
            break;
        }

        std::cout << "#### event: " << enqueued_event->tag() << ", payload: " << enqueued_event->payload() << " @ " << _name << std::endl;

        event_callback( enqueued_event );
    };
    std::cout << "bones_framework_dispatcher " << _name << " thread is stopping...." << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
