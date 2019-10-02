#ifndef __ZEN__BONES_FRAMEWORK_SERVICE__HPP
#define __ZEN__BONES_FRAMEWORK_SERVICE__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.hpp>
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

private:

    const std::string _name;
    const zen::bones_framework_dispatcher_shared _dispatcher;
};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_SERVICE__HPP
