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
#include <zen/quix/network/quix_network_shared_listener.cpp>
#include <zen/quix/utility/testing.h>
#include <zen/quix/network/quix_network_socket_listening.cpp>
#include <zen/quix/network/quix_network_socket_connected.cpp>
#include <zen/quix/network/quix_network_address_inet.cpp>
#include <zen/quix/network/quix_network_address_unix.cpp>
#include <memory>
#include <thread>
#include <sstream>
#include <functional>
#include <future>
#include <cstring>
#include <ctime>
#include <iostream>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace { struct address
{ int port_mem;
  static int next_port()
  { static int port =
 10000 + std::clock() % 40000;
    return ++port;}
  address() : port_mem( next_port() ) {};


  std::string inet( const std::string &hostname )
  { std::stringstream ss;
    ss << hostname << ":" << port_mem;
    return ss.str();}
  std::string any() { return inet( "" ); }
  std::string quix_memory_localhost() { return inet( "127.0.0.1" ); }


  std::string quix_messaging_unix()
  { std::stringstream ss;
    ss << "/tmp/domain" << port_mem << ".quix_messaging_unix";
    return ss.str();}};}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct plumbing
{ static
  void
  connection_quix_messaging_unix_fn( std::promise< int > &vprom,
    const std::string& listening_quix_messaging_unix_arg)
  { zen::quix_network_socket_listening< zen::quix_network_address_unix > listening( listening_quix_messaging_unix_arg );
    vprom.set_value( listening.accept() );}

  plumbing()
  { //structors_stack();
    //structors_heap();}

  void structors_stack()
  { std::promise< int > vprom_receiver;
    auto vfut_receiver =
 vprom_receiver.get_future();
    address addr_fd_receiver;
    std::thread fd_receiver_thread( plumbing::connection_quix_messaging_unix_fn,
      std::ref( vprom_receiver ),
      addr_fd_receiver.quix_messaging_unix());

    std::promise< int > vprom_sender;
    auto vfut_sender =
 vprom_sender.get_future();
    address addr_fd_sender;
    std::thread fd_sender_thread( plumbing::connection_quix_messaging_unix_fn,
      std::ref( vprom_sender ),
      addr_fd_sender.quix_messaging_unix());

    address addr_fd_listener;
     zen::quix_network_shared_listener listening( addr_fd_listener.any(),
      addr_fd_receiver.quix_messaging_unix(),
      addr_fd_sender.quix_messaging_unix());

    fd_receiver_thread.join();
    fd_sender_thread.join();

    CHECK( vfut_receiver.get() > 0 );
    CHECK( vfut_sender.get() > 0 );}

  void structors_heap()
  { std::promise< int > vprom_receiver;
    auto vfut_receiver =
 vprom_receiver.get_future();
    address addr_fd_receiver;
    std::thread fd_receiver_thread( plumbing::connection_quix_messaging_unix_fn,
      std::ref( vprom_receiver ),
      addr_fd_receiver.quix_messaging_unix());

    std::promise< int > vprom_sender;
    auto vfut_sender =
 vprom_sender.get_future();
    address addr_fd_sender;
    std::thread fd_sender_thread( plumbing::connection_quix_messaging_unix_fn,
      std::ref( vprom_sender ),
      addr_fd_sender.quix_messaging_unix());

    address addr_fd_listener;
     auto listening =
 std::make_quix_memory_shared< zen::quix_network_shared_listener >( addr_fd_listener.any(),
      addr_fd_receiver.quix_messaging_unix(),
      addr_fd_sender.quix_messaging_unix());

    fd_receiver_thread.join();
    fd_sender_thread.join();

    CHECK( vfut_receiver.get() > 0 );
    CHECK( vfut_sender.get() > 0 );}}
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
