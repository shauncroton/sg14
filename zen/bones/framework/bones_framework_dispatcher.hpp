#ifndef __ZEN__BONES_FRAMEWORK_DISPATCHER__HPP
#define __ZEN__BONES_FRAMEWORK_DISPATCHER__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <zen/bones/framework/bones_framework_acceptor.hpp>
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

public:

    using event_callback_function = std::function< void( zen::bones_framework_event_shared & ) >;

    using queue_content = std::pair<
        event_callback_function,
        zen::bones_framework_event_shared
    >;

    template< typename State >
    class impl;

    template<
        typename State,
        typename ...Args
    >
    static zen::bones_framework_dispatcher_shared
    make( Args ...args )
    {
        return std::make_shared< impl< State > >(
            std::forward< Args >( args )...
        );
    }

    void
    enqueue(
        event_callback_function &event_callback_,
        const zen::bones_framework_event_shared &enqueued_event_
    );

    const std::string &
    get_name() const
    {
        return _name;
    }

    const zen::bones_framework_directory_shared &
    get_directory()
    {
        return _directory;
    }

    template< typename Manager >
    static void
    start_service(
        const std::shared_ptr< Manager > &derived_dispatcher_,
        const std::string &name_,
        zen::bones_framework_session_shared(*factory_)(
            const std::shared_ptr< Manager > &,
            const zen::bones_framework_accessor_shared &
        ));

private:

    void
    process_events(
        std::promise< void > start_thread
    );

private:

    const zen::bones_framework_directory_shared _directory;
    const std::string _name;

    std::mutex _processing_queue_mutex;
    std::condition_variable _processing_queue_condition_variable;
    std::queue< queue_content > _processing_queue;
    std::thread _processing_thread;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename State >
class zen::bones_framework_dispatcher::impl
    : public bones_framework_dispatcher
        , public std::enable_shared_from_this< impl< State > >
{
    impl< State >(
        std::string name_,
        zen::bones_framework_directory_shared directory_
    );
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename State >
zen::bones_framework_dispatcher::impl< State >::impl(
    std::string name_,
    zen::bones_framework_directory_shared directory_
)
    :
    bones_framework_dispatcher(
        std::move( name_ ),
        std::move( directory_ ))
{
    return;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename Manager >
void
zen::bones_framework_dispatcher::start_service(
    const std::shared_ptr< Manager > &derived_dispatcher_,
    const std::string &name_,
    zen::bones_framework_session_shared(*factory_)(
        const std::shared_ptr< Manager > &,
        const zen::bones_framework_accessor_shared &
    ))
{
    auto factory_function = [
        factory_,
        derived_dispatcher_
    ](
        const zen::bones_framework_accessor_shared &service_accessor
    ) -> zen::bones_framework_session_shared
    {
        return factory_(
            derived_dispatcher_,
            service_accessor
        );
    };

    auto service_acceptor = std::make_shared< zen::bones_framework_acceptor >(
        derived_dispatcher_,
        name_,
        zen::bones_framework_acceptor::session_factory_function( factory_function ));

    derived_dispatcher_->get_directory()->insert(
        name_,
        service_acceptor
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_DISPATCHER__HPP
