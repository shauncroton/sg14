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
#include <zen/quix/behaviour/quix_behaviour_event_publish.cpp>
#include <zen/quix/utility/testing.h>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { }

  void structors_heap()
  { }}
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
//
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif
