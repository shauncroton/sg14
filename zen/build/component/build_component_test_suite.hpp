#ifndef __ZEN__BUILD_COMPONENT_TESTS__HPP
#define __ZEN__BUILD_COMPONENT_TESTS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_component.h>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_component_test_suite
{
    build_component_test_suite(
        int argc_,
        char *argv_[]
    )
    {};

    ~build_component_test_suite()
    {};

    int
    run()
    {
        std::cout
            << "Running Component Tests"
            << std::endl;
        return 0;
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_COMPONENT_TESTS__HPP
