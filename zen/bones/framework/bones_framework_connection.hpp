#ifndef __ZEN__BONES_FRAMEWORK_CONNECTION__HPP
#define __ZEN__BONES_FRAMEWORK_CONNECTION__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <zen/bones/framework/bones_framework_accessor.hpp>
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
class zen::bones_framework_connection
{
    bones_framework_connection( const bones_framework_connection & ) = delete;

    bones_framework_connection &
    operator=( bones_framework_connection ) = delete;

    bones_framework_connection( bones_framework_connection && ) = delete;

    bones_framework_connection &
    operator=( bones_framework_connection && ) = delete;

public:

    ~bones_framework_connection();

    template<
        typename bones_framework_dispatcher
    >
    bones_framework_connection(
        std::string name_,
        zen::bones_framework_dispatcher_shared &dispatcher_
    );

    const std::string&
    name() const
    { return _name; }

private:

    const std::string _name;
    const zen::bones_framework_accessor_shared _accessor;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename bones_framework_dispatcher >
zen::bones_framework_connection::bones_framework_connection(
    std::string name_,
    zen::bones_framework_dispatcher_shared &dispatcher_
)
    : _name( std::move( name_ ))
    , _accessor(
        zen::bones_framework_accessor::factory(
            dispatcher_,
            _name
        ))
{
    std::cout
        << "bones_framework_connection "
        << _name
        << " is created"
        << std::endl;
}


///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
inline
zen::bones_framework_connection::~bones_framework_connection()
{
    std::cout
        << "bones_framework_connection "
        << _name
        << " is destroyed"
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_CONNECTION__HPP
