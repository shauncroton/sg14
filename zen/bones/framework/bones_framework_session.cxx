#include "bones_framework_directory.cpp"
#include "bones_framework_dispatcher.cpp"
#include "bones_framework_event.cpp"
#include "bones_framework_accessor.cpp"
#include "bones_framework_acceptor.cpp"
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_unit.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
int
main(
    int argc,
    char *argv[]
)
{
    return build_unit_test_suite(
        argc,
        argv
    ).run();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
