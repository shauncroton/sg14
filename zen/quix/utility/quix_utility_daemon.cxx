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
#include <zen/build/build_unit.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
int main ( int argc, char* argv[] )
{
  return build_unit_test_suite( argc, argv ).run();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///

#if 0

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/utility/quix_utility_daemon.cpp>
//#include <zen/quix/node/quix_node.cpp>
#include <zen/quix/utility/quix_utility_configuration.cpp>
#include <zen/quix/memory/quix_memory_mapped.cpp>
#include <zen/quix/utility/testing.h>
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct plumbing
{
  plumbing()
  {
    structors_stack();
    structors_heap();
    copy_constructor();
    move_constructor();
    copy_assignment();
    move_assignment();
  }

  void structors_stack()
  {
  }

  void structors_heap()
  {
  }

  void copy_constructor()
  {
  }

  void move_constructor()
  {
  }

  void copy_assignment()
  {
  }

  void move_assignment()
  {
  }
}
plumbing;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct Runquix_utility_daemon
{
  Runquix_utility_daemon()
  {
    StreamParsing();
  }

  void StreamParsing()
  {
  }
}
runquix_utility_daemon;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif