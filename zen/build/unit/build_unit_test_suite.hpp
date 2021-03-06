#ifndef __ZEN__BUILD_UNIT_TESTS__HPP
#define __ZEN__BUILD_UNIT_TESTS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_unit.h>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_unit_test_suite
{
    build_unit_test_suite(
        int argc_,
        char *argv_[]
    )
    {};

    ~build_unit_test_suite()
    {};

    int
    run()
    {
        std::cout
            << "Running Unit Tests"
            << std::endl;
        return 0;
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_UNIT_TESTS__HPP
