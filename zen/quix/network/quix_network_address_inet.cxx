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
#include <zen/quix/network/quix_network_address_inet.cpp>
#include <zen/quix/utility/testing.h>
#include <memory>
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
        std::string address_arg( "quix_memory_localhost:12345" );
        zen::quix_network_address_inet address( address_arg );
  }

  void structors_heap()
  {
        std::string address_arg( "quix_memory_localhost:12345" );
        auto address = std::make_quix_memory_shared< zen::quix_network_address_inet >( address_arg );
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
    addr();
    size();
  }

  void addr()
  {
        std::string address_arg( "quix_memory_localhost:12345" );
        zen::quix_network_address_inet address( address_arg );

    struct sockaddr_in sa;
    bzero( &sa, sizeof( sa ) );
      sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr( "quix_memory_localhost" );
    sa.sin_port = htons( 12345 );

    CHECK( address.addr()->sa_family == reinterpret_cast< struct sockaddr& >( sa ).sa_family );
    const struct sockaddr_in *address_ptr = reinterpret_cast< const struct sockaddr_in* >( address.addr() ) ;
    CHECK( address_ptr->sin_family == sa.sin_family );
    CHECK( address_ptr->sin_addr.s_addr == sa.sin_addr.s_addr );
    CHECK( address_ptr->sin_port == sa.sin_port );
  }

  void size()
  {
        std::string address_arg( "quix_memory_localhost:12345" );
        zen::quix_network_address_inet address( address_arg );

    CHECK( address.size() == sizeof( sockaddr_in ) );
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