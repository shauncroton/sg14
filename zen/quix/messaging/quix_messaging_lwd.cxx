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
#include <zen/quix/messaging/quix_messaging_lwd.cpp>
#include <zen/quix/utility/testing.h>
#include <memory>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ typedef struct
    { char id;
    short key;
        int data;}
    event_type;

  using transport_type =
 zen::quix_messaging_lwd< event_type >;
  char data[ 65536 ];

  plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { transport_type quix_messaging_lwd( (void*)data, 1, {2} );}

  void structors_heap()
  { using follow_list_type =
 transport_type::follow_list_type;
    auto quix_messaging_lwd1 =
 std::make_quix_memory_shared< transport_type >( (void*)data, 2, follow_list_type( { 1 } ) );}}
plumbing;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct api
{ api()
  { aquire_test();
    aquire();
    commit();
    reaquire_test();
    reaquire();
    release();}

  void aquire_test()
  { return;}

  void aquire()
  { return;}

  void commit()
  { return;}

  void reaquire_test()
  { return;}

  void reaquire()
  { return;}

  void release()
  { return;}}
api;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct scenarios
{ using transport_type =
 zen::quix_messaging_lwd< uint64_t >;
  char data[ 1024 * 1024 * 1024 ];

  scenarios()
  { basic_three_stage_sequence();
        basic_three_stage_sequence_with_batching();}

  void basic_three_stage_sequence()
    { transport_type quix_node_injector( (void*)data, 1, {3} );
    transport_type quix_node_processor( (void*)data, 2, {1} );
    transport_type quix_node_terminator( (void*)data, 3, {2} );

    uint64_t &value1 =
 quix_node_injector.aquire();
    value1 =
 10;
    quix_node_injector.commit();

    uint64_t &value2 =
 quix_node_processor.reaquire();
    CHECK( value1 ==
 value2 );
        value2 =
 20;
    quix_node_processor.commit();

    uint64_t &value3 =
 quix_node_terminator.reaquire();
    CHECK( value2 ==
 value3 );
        quix_node_terminator.release();}

  void basic_three_stage_sequence_with_batching()
    { transport_type quix_node_injector( (void*)data, 1, {3} );
    transport_type quix_node_processor( (void*)data, 2, {1} );
    transport_type quix_node_terminator( (void*)data, 3, {2} );

    uint64_t &value11 =
 quix_node_injector.aquire();
    value11 =
 11;

    uint64_t &value12 =
 quix_node_injector.aquire();
    value12 =
 12;

    uint64_t &value13 =
 quix_node_injector.aquire();
    value13 =
 13;

    quix_node_injector.commit();
    quix_node_injector.commit();
    quix_node_injector.commit();
    CATCH( quix_node_processor.commit(), std::runtime_error, "commit called on event that was not aquired" );

    uint64_t &value21 =
 quix_node_processor.reaquire();
    CHECK( value11 ==
 value21 );
        value21 =
 21;

    uint64_t &value22 =
 quix_node_processor.reaquire();
    CHECK( value12 ==
 value22 );
        value22 =
 22;

    uint64_t &value23 =
 quix_node_processor.reaquire();
    CHECK( value13 ==
 value23 );
        value23 =
 23;

    quix_node_processor.commit();
    quix_node_processor.commit();
    quix_node_processor.commit();
    CATCH( quix_node_processor.commit(), std::runtime_error, "commit called on event that was not aquired" );

    uint64_t &value31 =
 quix_node_terminator.reaquire();
    CHECK( value21 ==
 value31 );

    uint64_t &value32 =
 quix_node_terminator.reaquire();
    CHECK( value22 ==
 value32 );

    uint64_t &value33 =
 quix_node_terminator.reaquire();
    CHECK( value23 ==
 value33 );

        quix_node_terminator.release();
        quix_node_terminator.release();
        quix_node_terminator.release();
    CATCH( quix_node_terminator.release(), std::runtime_error, "release called on event that was not aquired" );}}
scenarios;
//
///
#endif
