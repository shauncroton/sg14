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

//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#include <zen/quix/messaging/quix_messaging_uni.cpp>
#include <zen/quix/utility/testing.h>
#include <memory>
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct plumbing
{
  typedef struct
    {
        char id;
    short key;
        int data;
    }
    event_type;

  using transport_type = zen::quix_messaging_uni< event_type >;
  char data[ 65536 ];

  plumbing()
  {
    structors_stack();
    structors_heap();
  }

  void structors_stack()
  {
    transport_type quix_messaging_uni( (void*)data, 1, {2} );
  }

  void structors_heap()
  {
    using follow_list_type = transport_type::follow_list_type;
    auto quix_messaging_uni1 = std::make_quix_memory_shared< transport_type >( (void*)data, 1, follow_list_type( { 2 } ) );
  }
}
plumbing;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct api
{
  using transport_type = zen::quix_messaging_uni< uint64_t >;
  char data[ 65536 ];

  api()
  {
    aquire_test();
    aquire();
    commit();
    reaquire_test();
    reaquire();
    release();
         basic_three_stage_sequence();
  }

  void aquire_test()
  {
    return;
  }

  void aquire()
  {
    return;
  }

  void commit()
  {
    return;
  }

  void reaquire_test()
  {
    return;
  }

  void reaquire()
  {
    return;
  }

  void release()
  {
    return;
  }

  void basic_three_stage_sequence()
    {
    transport_type quix_messaging_uni( (void*)data, 1, {2} );
    }
}
api;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct scenarios
{
  using transport_type = zen::quix_messaging_uni< uint64_t >;
  char data[ 1024 * 1024 * 1024 ];

  scenarios()
  {
         basic_three_stage_sequence();
  }

  void basic_three_stage_sequence()
    {
    transport_type quix_node_injector( (void*)data, 1, {0} );
    transport_type quix_node_processor( (void*)data, 2, {1} );
    transport_type quix_node_terminator( (void*)data, 3, {2} );

    uint64_t &value1 = quix_node_injector.aquire();
    value1 = 10;
    quix_node_injector.commit();

    uint64_t &value2 = quix_node_processor.reaquire();
    CHECK( value1 == value2 );
        value2 = 20;
    quix_node_processor.commit();

    uint64_t &value3 = quix_node_terminator.reaquire();
    CHECK( value2 == value3 );
        quix_node_terminator.release();
    }
}
scenarios;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif