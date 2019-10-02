///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.hpp>
#include <strings.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_acceptor::bones_framework_acceptor(
    zen::bones_framework_dispatcher_shared dispatcher_,
    std::string name_,
    session_factory_function factory_
)
    : _name( std::move( name_ ))
    , _service_dispatcher( std::move( dispatcher_ ))
    , _factory_function( std::move( factory_ ))
{
    bool is_address = _name.find( ':' ) != std::string::npos;
    if( is_address )
    {
        std::promise< void > start_thread;
        auto thread_started = start_thread.get_future();
        _listener_thread = std::thread(
            &zen::bones_framework_acceptor::listener,
            this,
            _name,
            this,
            std::move( start_thread ));
        thread_started.get();
    }
    std::cout
        << "acceptor "
        << _name
        << " is created"
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_acceptor::~bones_framework_acceptor()
{
    if( _sock_fd >= 0 )
    {
        close( _sock_fd );
        _listener_thread.join();
    }

    std::cout
        << "acceptor "
        << _name
        << " is destroyed"
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor_shared
zen::bones_framework_acceptor::grant(
    zen::bones_framework_dispatcher_shared &dispatcher_,
    const std::string &name_
)
{
    zen::bones_framework_accessor_shared second_accessor = std::make_shared< zen::bones_framework_accessor >(
        _service_dispatcher,
        name_ + ".2"
    );
    zen::bones_framework_accessor_shared first_accessor = std::make_shared< zen::bones_framework_accessor >(
        dispatcher_,
        name_ + ".1",
        second_accessor
    );
    first_accessor->set_entangled( second_accessor );
    second_accessor->set_entangled( first_accessor );
    zen::bones_framework_session_shared session_instance = _factory_function( second_accessor );
    second_accessor->set_session_ownership( session_instance );
    return first_accessor;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_acceptor::listener(
    std::string address,
    zen::bones_framework_acceptor *listener_acceptor,
    std::promise< void > start_thread
)
{
    std::cout
        << "acceptor "
        << _name
        << " thread is starting...."
        << std::endl;

    auto it = address.find( ':' );
    auto host = address.substr(
        0,
        it
    );
    auto port = address.substr( ++it );

    /// Make a new socket
    _sock_fd = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );
    if( _sock_fd < 0 )
    {
        std::cout
            << "ERROR opening socket"
            << std::endl;
    }

    /// Bind address to socket
    struct sockaddr_in server_address;
    bzero(( char * ) &server_address,
        sizeof( server_address ));
    auto port_no = atoi( port.c_str());
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons( port_no );
    auto r = bind(
        _sock_fd,
        ( struct sockaddr * ) &server_address,
        sizeof( server_address ));
    if( r < 0 )
    {
        std::cout
            << "ERROR on binding"
            << std::endl;
    }

    /// Make a listening socket
    listen(
        _sock_fd,
        5
    );

    /// Accept an incoming connection
    start_thread.set_value();
    while( true )
    {
        struct sockaddr_in client_address;
        socklen_t client_length = sizeof( client_address );
        std::cout
            << "acceptor "
            << _name
            << " thread is waiting...."
            << std::endl;
        auto new_sock_fd = accept(
            _sock_fd,
            ( struct sockaddr * ) &client_address,
            &client_length
        );
        std::cout
            << "acceptor "
            << _name
            << " thread is working...."
            << std::endl;
        if( new_sock_fd < 0 )
        {
            break;
        }

        //            uint32_t ready =
        //0xCAFEBABE;
        //            send(new_sock_fd, &ready, sizeof(ready),0);
        //            ready =
        //0;
        //            recv(new_sock_fd, &ready, sizeof(ready),0);
        //            if( ready !=
        //0xCAFEBABE ) throw std::runtime_error( "connection handshake bad" );

        auto first_accessor = grant(
            _service_dispatcher,
            address
        );
        first_accessor->start_dispatcher(
            first_accessor,
            new_sock_fd
        );
    }
    std::cout
        << "acceptor "
        << _name
        << " thread is stopping...."
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
