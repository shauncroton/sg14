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
#include <zen/quix/behaviour/quix_behaviour_file_write.cpp>
#include <zen/quix/utility/testing.h>
#include <types/event.hpp>
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { std::string filename( "/tmp/mmfile0.dat" );
    zen::quix_behaviour_file_write< types::event > quix_behaviour_file_write( filename );}

  void structors_heap()
  { std::string filename( "/tmp/mmfile0.dat" );
    auto quix_behaviour_file_write =
 std::make_quix_memory_shared< zen::quix_behaviour_file_write< types::event > >( filename );}}
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

        std::string filename( "/tmp/quix_behaviour_file_write.txt" );
        { zen::quix_behaviour_file_write< types::event > quix_behaviour_file_write( filename );
      for( const std::string &line : lines )
          { types::event::buffer_type buffer;
              std::memcpy( buffer.data, line.c_str(), line.size() );
              buffer.size =
 line.size();
            types::event event;
        event.buffer_mem =
 &buffer;
        quix_behaviour_file_write( event );}}

    std::ifstream fs( filename );

        std::string input;
    for( const auto &line : lines )
        { std::getline( fs, input );
            std::cout << line << " ==
 " << input << "\n";
          CHECK( line ==
 input );}
        std::getline( fs, input );
      CHECK( input.size() ==
 0 );
      CHECK( fs.eof() );}}
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
