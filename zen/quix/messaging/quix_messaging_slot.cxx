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
#include <zen/quix/messaging/quix_messaging_slot.cpp>
#include <zen/quix/messaging/quix_messaging_uni.cpp>
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
struct scenarios
{ typedef struct
    { char id;
    short key;
        int data;}
    event_type;

  char data[ 1024 * 1024 * 1024 ];

  scenarios()
  { basic_three_stage_sequence();}

  void basic_three_stage_sequence()
    { using transport_type =
 zen::quix_messaging_uni< event_type >;

    transport_type quix_node_injector( (void*)data, 1, {0} );
        { auto quix_messaging_slot =
 zen::make_quix_messaging_aquire_commit_slot( quix_node_injector );
      quix_messaging_slot->id =
 1;
      quix_messaging_slot->key =
 22;
      quix_messaging_slot->data =
 3333;}

    transport_type quix_node_processor( (void*)data, 2, {1} );
        { auto quix_messaging_slot =
 zen::make_quix_messaging_reaquire_commit_slot( quix_node_processor );
      CHECK( quix_messaging_slot->id ==
 1 );
      CHECK( quix_messaging_slot->key ==
 22 );
      CHECK( quix_messaging_slot->data ==
 3333 );
      quix_messaging_slot->id =
 4;
      quix_messaging_slot->key =
 55;
      quix_messaging_slot->data =
 666;}

    transport_type quix_node_terminator( (void*)data, 3, {2} );
        { auto quix_messaging_slot =
 zen::make_quix_messaging_reaquire_release_slot( quix_node_terminator );
      CHECK( quix_messaging_slot->id ==
 4 );
      CHECK( quix_messaging_slot->key ==
 55 );
      CHECK( quix_messaging_slot->data ==
 666 );}}}
scenarios;
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif
