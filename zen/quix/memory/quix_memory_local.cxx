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
#include <zen/quix/memory/quix_memory_local.cpp>
#include <zen/quix/utility/testing.h>
#include <memory>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
constexpr int mb =
 1024576;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { zen::quix_memory_local quix_memory_local1( mb );}

  void structors_heap()
  { auto quix_memory_local1 =
 std::make_quix_memory_shared< zen::quix_memory_local >( mb );}}
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
