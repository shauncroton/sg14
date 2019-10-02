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
#include <zen/quix/node/quix_node_injector.cpp>
#include <zen/quix/utility/testing.h>
#include <zen/quix/memory/quix_memory_local.cpp>
#include <zen/quix/messaging/quix_messaging_uni.cpp>
#include <zen/quix/behaviour/quix_behaviour_event_publish.cpp>
#include <memory>
#include <cstring>
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct plumbing
{
  plumbing()
  {
    structors_stack();
    structors_heap();
  }

  void structors_stack()
  {
    using transport_type = zen::quix_messaging_uni< uint64_t >;
        zen::quix_memory_local transport_memory( 1048576 );
    std::memset( transport_memory.data(), 0, transport_memory.size() );
        transport_type transport( transport_memory.data(), 1, { 2 } );

    using quix_behaviour_type = zen::quix_behaviour_event_publish< uint64_t >;
        zen::quix_memory_local quix_behaviour_memory( 1048576 );
        quix_behaviour_type behaviour( quix_behaviour_memory.data(), 1 );

    using quix_node_injector_type = zen::quix_node_injector< transport_type, quix_behaviour_type >;
    quix_node_injector_type quix_node_injector( transport, behaviour );
  }

  void structors_heap()
  {
    using transport_type = zen::quix_messaging_uni< uint64_t >;
        zen::quix_memory_local transport_memory( 1048576 );
    std::memset( transport_memory.data(), 0, transport_memory.size() );
        transport_type transport( transport_memory.data(), 1, { 2 } );

    using quix_behaviour_type = zen::quix_behaviour_event_publish< uint64_t >;
        zen::quix_memory_local quix_behaviour_memory( 1048576 );
        quix_behaviour_type behaviour( quix_behaviour_memory.data(), 1 );

    using quix_node_injector_type = zen::quix_node_injector< transport_type, quix_behaviour_type >;
    auto quix_node_injector = std::make_quix_memory_shared< quix_node_injector_type >( transport, behaviour );
  }
}
plumbing;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct api
{
  api()
  {
    test();
  }

  void test()
  {
  }
}
api;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct scenarios
{
  scenarios()
  {
    test();
  }

  void test()
  {
  }
}
scenarios;
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif