#include <zen/parts/utility/parts_utility_functions.cpp>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_unit.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_unit_test_0000
    : build_unit_test_case
{
    build_unit_test_0000()
        : build_unit_test_case(
        "testcase_one",
        {
            test::feature(
                "foo",
                &build_unit_test_0000::function_test_one
            ),
            test::feature(
                "bar",
                &build_unit_test_0000::function_test_two
            )
        }
    )
    {
        // Set up test here
    }

    void
    function_test_one()
    {
        MATCHES( "What are we checking",
            true,
            true );

        DIFFERS( "What are we failing",
            true,
            false );

        CATCHES( "What are we catching",
            std::logic_error( "logic error thrown" ),
            throw std::logic_error( "logic error thrown" ));
    }

    void
    function_test_two()
    {
        MATCHES( "What are we checking",
            true,
            true );

        DIFFERS( "What are we failing",
            true,
            false );

        CATCHES( "What are we catching",
            std::logic_error( "logic error thrown" ),
            throw std::logic_error( "logic error thrown" ));
    }

    ~build_unit_test_0000()
    {
        // Pull down test here
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct build_unit_test_0001
    : build_unit_test_case
{
    build_unit_test_0001()
        : build_unit_test_case(
        "testcase_one",
        {
            test(
                "foo",
                &build_unit_test_0001::function_test_one
            ),
            test(
                "bar",
                &build_unit_test_0001::function_test_two
            )
        }
    )
    {
        // Set up test here
    }

    void
    function_test_one()
    {
        MATCHES( "What are we checking",
            true,
            true );

        DIFFERS( "What are we failing",
            true,
            false );

        CATCHES( "What are we catching",
            throw std::logic_error( "logic error thrown" ),
            std::logic_error,
            "logic error thrown" );
    }

    void
    function_test_two()
    {
        MATCHES( "What are we checking",
            true,
            true );

        DIFFERS( "What are we failing",
            true,
            false );

        CATCHES( "What are we catching",
            std::logic_error( "logic error thrown" ),
            throw std::logic_error( "logic error thrown" ));
    }

    ~build_unit_test_0001()
    {
        // Pull down test here
    }
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
int
main(
    int argc,
    char *argv[]
)
{
    build_unit_test_suite<
        build_unit_test_one,
        build_unit_test_two
    > unit_test_suite;

    return unit_test_suite.run(
        argc,
        argv
    );
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
