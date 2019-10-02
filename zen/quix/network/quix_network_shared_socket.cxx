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
#include <zen/quix/network/quix_network_shared_socket.cpp>
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
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
namespace {
struct address
{
  int port_mem;
  static int next_port()
  {
    static int port = 10000 + std::clock() % 40000;
    return ++port;
  }
  address() : port_mem( next_port() ) {};


  std::string inet( const std::string &hostname ) 
  {
    std::stringstream ss;
    ss << hostname << ":" << port_mem;
    return ss.str();
  }
  std::string any() { return inet( "" ); }
  std::string quix_memory_localhost() { return inet( "127.0.0.1" ); }


  std::string quix_messaging_unix()
  {
    std::stringstream ss;
    ss << "/tmp/domain" << port_mem << ".quix_messaging_unix";
    return ss.str();
  }
};}
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
struct plumbing
{
  static
  void
  fd_listener_fn(
    const std::string& fd_listener_arg,
      const std::string& fd_receiver_arg,
    const std::string& fd_sender_arg
        )
    {
    zen::quix_network_shared_listener fd_listener(
      fd_listener_arg,
      fd_receiver_arg,
      fd_sender_arg
      );
    fd_listener();
    }

  static
  void
  fd_sender_fn(
    const std::string& fd_sender_arg,
    const std::string& sender_buff
        )
    {
        zen::quix_network_shared_socket fd_sender( fd_sender_arg );
    auto sender = fd_sender();
    sender->send( sender_buff.data(), sender_buff.size() );
    }


  plumbing()
  {
    structors_stack();
    structors_heap();
  }

  void structors_stack()
  {
    address addr_fd_listener;
    address addr_fd_receiver;
    address addr_fd_sender;

    std::thread fd_listener_thread(
      plumbing::fd_listener_fn,
      addr_fd_listener.any(),
      addr_fd_receiver.quix_messaging_unix(),
      addr_fd_sender.quix_messaging_unix()
      );

        std::string sender_buff( "He sells sea shells" );

    std::thread fd_sender_thread(
      plumbing::fd_sender_fn,
      addr_fd_sender.quix_messaging_unix(),
      sender_buff
      );

        zen::quix_network_shared_socket fd_receiver( addr_fd_receiver.quix_messaging_unix() );
      zen::quix_network_socket_connected< zen::quix_network_address_inet > client( addr_fd_listener.quix_memory_localhost() );
      auto receiver = fd_receiver();

    char client_recv_buff[1024];
    memset( client_recv_buff, 0, 1024 );
    auto client_recvd = client.recv( client_recv_buff, 1024 );

        std::string client_send_buff( "by the sea shore" );
    auto client_sent = client.send( client_send_buff.data(), client_send_buff.size() );

    char receiver_recv_buff[1024];
    memset( receiver_recv_buff, 0, 1024 );
    auto receiver_recvd = receiver->recv( receiver_recv_buff, 1024 );

    fd_listener_thread.join();
        fd_sender_thread.join();

    CHECK( sender_buff.size() == client_recvd );
    CHECK( sender_buff == std::string( client_recv_buff, client_recvd ) );

    CHECK( client_send_buff.size() == client_sent );
    CHECK( client_send_buff.size() == receiver_recvd );
    CHECK( client_send_buff == std::string( receiver_recv_buff, receiver_recvd ) );
  }

  void structors_heap()
  {
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