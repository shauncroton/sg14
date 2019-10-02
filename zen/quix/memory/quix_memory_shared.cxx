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
#if 0

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/memory/quix_memory_shared.cpp>
#include <zen/quix/utility/testing.h>
#include <memory>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { zen::quix_memory_shared quix_memory_shared1( 0, 1048576 );}

  void structors_heap()
  { auto quix_memory_shared1 =
 std::make_quix_memory_shared< zen::quix_memory_shared >( 0, 1048576);}}
plumbing;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct api
{ api()
  { test();}

  void test()
  { }}
api;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct scenarios
{ scenarios()
  { test();}

  void test()
  { }}
scenarios;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif
