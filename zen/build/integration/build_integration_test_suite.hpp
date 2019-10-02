#ifndef __ZEN__BUILD_INTEGRATION_TESTS__HPP
#define __ZEN__BUILD_INTEGRATION_TESTS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_integration.h>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_integration_test_suite
{
    build_integration_test_suite(
        int argc_,
        char *argv_[]
    )
    {
    };

    ~build_integration_test_suite()
    {
    };

    int
    run()
    {
        std::cout << "Running Integration Tests" << std::endl;
        return 0;
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_INTEGRATION_TESTS__HPP
