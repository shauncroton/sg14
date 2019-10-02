#ifndef __ZEN__BUILD_SYSTEM_TESTS__HPP
#define __ZEN__BUILD_SYSTEM_TESTS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_system.h>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_system_test_suite
{
    build_system_test_suite(
        int argc_,
        char *argv_[]
    )
    {};

    ~build_system_test_suite()
    {};

    int
    run()
    {
        std::cout
            << "Running System Tests"
            << std::endl;
        return 0;
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_SYSTEM_TESTS__HPP
