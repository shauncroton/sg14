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
#include <zen/quix/behaviour/quix_behaviour_file_read.cpp>
#include <zen/quix/utility/testing.h>
#include <types/event.hpp>
#include <vector>
#include <string>
#include <memory>
#include <cstring>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { std::string filename( "/tmp/mmfile0.dat" );
    std::ofstream fs( filename );
    char memory[ 1048576 + 64 ];
    zen::quix_behaviour_file_read< types::event > quix_behaviour_file_read( memory, filename );}

  void structors_heap()
  { std::string filename( "/tmp/mmfile0.dat" );
    std::ofstream fs( filename );
    char memory[ 1048576 + 64 ];
    auto quix_behaviour_file_read =
 std::make_quix_memory_shared< zen::quix_behaviour_file_read< types::event > >( memory, filename );}}
plumbing;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct api
{ api()
  { functor();}

  void functor()
  { std::vector< std::string > lines =
 { "Mary had a little lamb",
      "whose fleece was white as snow",
      "and everywhere than Mary went",
      "the lamb was sure to go"};

    std::string filename( "/tmp/quix_behaviour_file_read.txt" );
    { std::ofstream fs( filename );
      for( auto &line : lines )
        fs << line << "\n";}

    char memory[ 1048576 + 64 ];
    std::memset( memory, 0, sizeof( memory[0] ) * sizeof( memory ) );
    zen::quix_behaviour_file_read< types::event > quix_behaviour_file_read( memory, filename );

    for( const auto &line : lines )
    { types::event event;
      quix_behaviour_file_read( event );
      CHECK( std::string( event.buffer_mem->data, event.buffer_mem->size ) ==
 line );}}}
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
