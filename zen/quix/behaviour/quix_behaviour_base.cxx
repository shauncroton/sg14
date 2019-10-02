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
#include <zen/quix/behaviour/quix_behaviour_base.cpp>
#include <zen/quix/utility/testing.hpp>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ plumbing()
  { structors_stack();
    structors_heap();
    copy_constructor();
    move_constructor();
    copy_assignment();
    move_assignment();}

  void structors_stack()
  { }

  void structors_heap()
  { }

  void copy_constructor()
  { }

  void move_constructor()
  { }

  void copy_assignment()
  { }

  void move_assignment()
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
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif
