#ifndef __ZEN__BUILD_OPERATION_TESTS__HPP
#define __ZEN__BUILD_OPERATION_TESTS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_operation.h>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_operation_test_suite
{
    build_operation_test_suite(
        int argc_,
        char *argv_[]
    )
    {
    };

    ~build_operation_test_suite()
    {
    };

    int
    run()
    {
        std::cout << "Running Operation Tests" << std::endl;
        return 0;
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_OPERATION_TESTS__HPP
