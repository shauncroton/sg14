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
#include <zen/quix/network/quix_network_address_unix.cpp>
#include <zen/quix/utility/testing.h>
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
        std::string address_arg( "/tmp/quix_network_address_unix_test.quix_messaging_unix" );
        zen::quix_network_address_unix address( address_arg );
  }

  void structors_heap()
  {
        std::string address_arg( "/tmp/quix_network_address_unix_test.quix_messaging_unix" );
        auto address = std::make_quix_memory_shared< zen::quix_network_address_unix >( address_arg );
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
        std::string address_arg( "/tmp/quix_network_address_unix_test.quix_messaging_unix" );
        zen::quix_network_address_unix address( address_arg );

    struct sockaddr_un sa;
    bzero( &sa, sizeof( sa ) );
      sa.sun_family = AF_LOCAL;
      strcpy( sa.sun_path, address_arg.c_str() );

    CHECK( address.addr()->sa_family == reinterpret_cast< struct sockaddr& >( sa ).sa_family );
    const struct sockaddr_un *address_ptr = reinterpret_cast< const struct sockaddr_un* >( address.addr() ) ;
    CHECK( address_ptr->sun_family == sa.sun_family );
    CHECK( std::strcmp( address_ptr->sun_path, sa.sun_path ) == 0 );
  }

  void size()
  {
        std::string address_arg( "/tmp/quix_network_address_unix_test.quix_messaging_unix" );
        zen::quix_network_address_unix address( address_arg );

    CHECK( address.size() == sizeof( sockaddr_un ) );
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