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
#include <zen/quix/messaging/quix_messaging_mcd.cpp>
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
 zen::quix_messaging_mcd< event_type >;
  char meta[ 65536 ];

  plumbing()
  { structors_stack();
    structors_heap();}

  void structors_stack()
  { transport_type quix_messaging_mcd1( (void*)meta, 1, 1, { { 2, 1 } } );
        transport_type quix_messaging_mcd2( (void*)meta, 3,    { { 4, 1 } } );}

  void structors_heap()
  { using follow_list_type =
 transport_type::follow_list_type;
    auto quix_messaging_mcd1 =
 std::make_quix_memory_shared< transport_type >( (void*)meta, 2,    follow_list_type( { { 1, 1 } } ) );
        auto quix_messaging_mcd2 =
 std::make_quix_memory_shared< transport_type >( (void*)meta, 2, 4, follow_list_type( { { 1, 4 } } ) );}}
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
 zen::quix_messaging_mcd< int >;
  char meta[ 1024 * 1024 * 1024 ];

  scenarios()
  { basic_three_stage_sequence();
    basic_quix_messaging_dual_channel_cross_sequence();}

  void basic_three_stage_sequence()
    { memset ( meta, 0, sizeof( meta ) );

    transport_type quix_node_injector( (void*)meta, 1, 1, {{3,1}} );
    transport_type quix_node_processor( (void*)meta, 2,    {{1,1}} );
    transport_type quix_node_terminator( (void*)meta, 3,    {{2,1}} );

    CHECK( quix_node_injector.aquire_test() ==
 true );
    CHECK( quix_node_injector.reaquire_test() ==
 false );
    CATCH( quix_node_injector.reaquire(), std::runtime_error, "reaquire called by an quix_node_injector" );
    CATCH( quix_node_injector.commit(), std::runtime_error, "commit called before aquire/reaquire" );
    CATCH( quix_node_injector.release(), std::runtime_error, "release called before aquire/reaquire" );
    int &value1 =
 quix_node_injector.aquire();
    CHECK( quix_node_injector.aquire_test() ==
 false );
    CATCH( quix_node_injector.aquire(), std::runtime_error, "aquire called before current released/committed" );
    CATCH( quix_node_injector.reaquire(), std::runtime_error, "reaquire called before current released/committed" );
    value1 =
 10;
    int *value1addr =
 &value1;
    quix_node_injector.commit();
    CATCH( quix_node_injector.commit(), std::runtime_error, "commit called before aquire/reaquire" );
    CATCH( quix_node_injector.release(), std::runtime_error, "release called before aquire/reaquire" );

    CHECK( quix_node_processor.aquire_test() ==
 false );
    CHECK( quix_node_processor.reaquire_test() ==
 true );
    CATCH( quix_node_processor.aquire(), std::runtime_error, "aquire called when not an quix_node_injector" );
    CATCH( quix_node_processor.commit(), std::runtime_error, "commit called before aquire/reaquire" );
    CATCH( quix_node_processor.release(), std::runtime_error, "release called before aquire/reaquire" );
    int &value2 =
 quix_node_processor.reaquire();
    CHECK( quix_node_processor.reaquire_test() ==
 false );
    CATCH( quix_node_processor.aquire(), std::runtime_error, "aquire called before current released/committed" );
    CATCH( quix_node_processor.reaquire(), std::runtime_error, "reaquire called before current released/committed" );
    CHECK( value1 ==
 value2 );
    int *value2addr =
 &value2;
    CHECK( value1addr ==
 value2addr );
        value2 =
 20;
    quix_node_processor.commit();
    CATCH( quix_node_processor.commit(), std::runtime_error, "commit called before aquire/reaquire" );
    CATCH( quix_node_processor.release(), std::runtime_error, "release called before aquire/reaquire" );

    CHECK( quix_node_terminator.aquire_test() ==
 false );
    CHECK( quix_node_terminator.reaquire_test() ==
 true );
    CATCH( quix_node_terminator.aquire(), std::runtime_error, "aquire called when not an quix_node_injector" );
    CATCH( quix_node_terminator.commit(), std::runtime_error, "commit called before aquire/reaquire" );
    CATCH( quix_node_terminator.release(), std::runtime_error, "release called before aquire/reaquire" );
    int &value3 =
 quix_node_terminator.reaquire();
    CHECK( quix_node_terminator.reaquire_test() ==
 false );
    CATCH( quix_node_terminator.aquire(), std::runtime_error, "aquire called before current released/committed" );
    CATCH( quix_node_terminator.reaquire(), std::runtime_error, "reaquire called before current released/committed" );
    CHECK( value2 ==
 value3 );
    int *value3addr =
 &value3;
    CHECK( value2addr ==
 value3addr );
        quix_node_terminator.release();
    CATCH( quix_node_terminator.commit(), std::runtime_error, "commit called before aquire/reaquire" );
    CATCH( quix_node_terminator.release(), std::runtime_error, "release called before aquire/reaquire" );}

  void basic_quix_messaging_dual_channel_cross_sequence()
    { memset ( meta, 0, sizeof( meta ) );

    // I1.1 \      / T4.X
    //        P3.X
    // I2.2 /      \ T5.X

    transport_type quix_node_injector11( (void*)meta, 1, 1, {{4,1}} );
        transport_type quix_node_injector22( (void*)meta, 2, 2, {{5,2}} );
        transport_type quix_node_processor3x( (void*)meta, 3,    {{1,1},{2,2}} );
        transport_type quix_node_terminator41( (void*)meta, 4,    {{3,1}} );
      transport_type quix_node_terminator52( (void*)meta, 5,    {{3,2}} );

    // Thru channel 1
        { CHECK( quix_node_injector11.aquire_test() ==
 true );
    int &value1 =
 quix_node_injector11.aquire();
    value1 =
 11;
    int *value1addr =
 &value1;
    quix_node_injector11.commit();

    CHECK( quix_node_processor3x.reaquire_test() ==
 true );
    int &value2 =
 quix_node_processor3x.reaquire();
    CHECK( value1 ==
 value2 );
    int *value2addr =
 &value2;
    CHECK( value1addr ==
 value2addr );
        value2 =
 21;
    quix_node_processor3x.commit();

    CHECK( quix_node_terminator41.reaquire_test() ==
 true );
    int &value3 =
 quix_node_terminator41.reaquire();
    CHECK( value2 ==
 value3 );
    int *value3addr =
 &value3;
    CHECK( value2addr ==
 value3addr );
        quix_node_terminator41.release();}

    // Thru channel 2
        { CHECK( quix_node_injector22.aquire_test() ==
 true );
    int &value1 =
 quix_node_injector22.aquire();
    value1 =
 12;
    int *value1addr =
 &value1;
    quix_node_injector22.commit();

    CHECK( quix_node_processor3x.reaquire_test() ==
 true );
    int &value2 =
 quix_node_processor3x.reaquire();
    CHECK( value1 ==
 value2 );
    int *value2addr =
 &value2;
    CHECK( value1addr ==
 value2addr );
        value2 =
 22;
    quix_node_processor3x.commit();

    CHECK( quix_node_terminator52.reaquire_test() ==
 true );
    int &value3 =
 quix_node_terminator52.reaquire();
    CHECK( value2 ==
 value3 );
    int *value3addr =
 &value3;
    CHECK( value2addr ==
 value3addr );
        quix_node_terminator52.release();}}}
scenarios;
//


///
#endif
