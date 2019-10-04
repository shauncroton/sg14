#ifndef __ZEN__BONES_FRAMEWORK_SERVICE__HPP
#define __ZEN__BONES_FRAMEWORK_SERVICE__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.hpp>
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
class zen::bones_framework_service
{
    bones_framework_service( const bones_framework_service & ) = delete;

    bones_framework_service &
    operator=( bones_framework_service ) = delete;

    bones_framework_service( bones_framework_service && ) = delete;

    bones_framework_service &
    operator=( bones_framework_service && ) = delete;

public:

    ~bones_framework_service();

    bones_framework_service(
        std::string name_,
        zen::bones_framework_dispatcher_shared dispatcher_
    );

    const std::string&
    name() const
    { return _name; }

    template< typename Manager >
    static void
    start(
        const std::shared_ptr< Manager > &derived_dispatcher_,
        const std::string &name_,
        zen::bones_framework_session_shared(*factory_)(
            const std::shared_ptr< Manager > &,
            const zen::bones_framework_accessor_shared &
        ));

    template<
        typename Manager,
        typename Session
    >
    static zen::bones_framework_session_shared
    factory(
        const std::shared_ptr< Manager > &session_dispatcher_,
        const zen::bones_framework_accessor_shared &session_accessor_
    );

private:

    const std::string _name;
    const zen::bones_framework_dispatcher_shared _dispatcher;
};


///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename Manager >
void
zen::bones_framework_service::start(
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
    ]( const zen::bones_framework_accessor_shared &service_accessor ) -> zen::bones_framework_session_shared
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

    derived_dispatcher_->directory()->insert(
        name_,
        service_acceptor
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename Manager,
    typename Session
>
zen::bones_framework_session_shared
zen::bones_framework_service::factory(
    const std::shared_ptr< Manager > &session_dispatcher_,
    const zen::bones_framework_accessor_shared &session_accessor_
)
{
    return std::make_shared< Session >(
        session_dispatcher_,
        session_accessor_
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_SERVICE__HPP
