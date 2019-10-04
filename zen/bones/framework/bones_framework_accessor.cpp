///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.hpp>
#include <strings.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor_shared
zen::bones_framework_accessor::factory(
    zen::bones_framework_dispatcher_shared dispatcher_,
    const std::string &name_
)
{
    return dispatcher_->directory()->lookup( name_ )->grant(
        dispatcher_,
        name_
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor_shared
zen::bones_framework_accessor::factory(
    zen::bones_framework_dispatcher_shared dispatcher_,
    const std::string &host_,
    int port_
)
{
    auto sock_fd = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );
    if( sock_fd < 0 )
    {
        std::cout
            << "ERROR opening socket"
            << std::endl;
        exit( 0 );
    }
    struct hostent *server = gethostbyname( host_.c_str());
    if( server == nullptr )
    {
        std::cout
            << "ERROR, no such host"
            << std::endl;
        exit( 0 );
    }
    struct sockaddr_in serv_addr;
    bzero(( char * ) &serv_addr,
        sizeof( serv_addr ));
    serv_addr.sin_family = AF_INET;
    bcopy(
        server->h_addr,
        ( char * ) &serv_addr.sin_addr.s_addr,
        server->h_length
    );
    serv_addr.sin_port = htons( port_ );
    if( connect(
        sock_fd,
        ( struct sockaddr * ) &serv_addr,
        sizeof( serv_addr )) < 0 )
    {
        std::cout
            << "ERROR connecting"
            << std::endl;
        exit( 0 );
    }

    //    uint32_t ready =
    //0xCAFEBABE;
    //    send(sock_fd, &ready, sizeof(ready),0);
    //    ready =
    //0;
    //    recv(sock_fd, &ready, sizeof(ready),0);
    //    if( ready !=
    //0xCAFEBABE )
    //        throw std::runtime_error("connection handshake bad");

    const std::string name = host_ + ":" + std::to_string( port_ );

    zen::bones_framework_accessor_shared second_accessor = std::make_shared< zen::bones_framework_accessor >(
        dispatcher_,
        name + ".2"
    );
    zen::bones_framework_accessor_shared first_accessor = std::make_shared< zen::bones_framework_accessor >(
        dispatcher_,
        name + ".1",
        second_accessor
    );
    first_accessor->set_entangled( second_accessor );
    second_accessor->set_entangled( first_accessor );
    second_accessor->start_dispatcher(
        second_accessor,
        sock_fd
    );
    return first_accessor;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor::bones_framework_accessor(
    zen::bones_framework_dispatcher_shared dispatcher_,
    std::string name_,
    zen::bones_framework_accessor_shared ownership_
)
    : _name( std::move( name_ ))
    , _service_dispatcher( std::move( dispatcher_ ))
    , _accessor_ownership( std::move( ownership_ ))
{
    std::cout
        << "zen::bones_framework_accessor "
        << _name
        << " is created"
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor::bones_framework_accessor(
    const zen::bones_framework_dispatcher_shared &dispatcher_,
    const std::string &name_
)
    : zen::bones_framework_accessor(
    dispatcher_,
    name_,
    nullptr
)
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_accessor::~bones_framework_accessor()
{
    if( _sock_fd >= 0 )
        close( _sock_fd );

    std::cout
        << "zen::bones_framework_accessor "
        << _name
        << " is destroyed"
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::start_dispatcher(
    zen::bones_framework_accessor_shared me_shared_,
    int sock_fd_
)
{
    std::thread(
        &zen::bones_framework_accessor::dispatcher,
        this,
        me_shared_,
        sock_fd_
    ).detach();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::set_entangled( zen::bones_framework_accessor_shared &entangled_ )
{ _entangled = entangled_; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
void
zen::bones_framework_accessor::set_session_ownership( zen::bones_framework_session_shared &session_instance_ )
{ _session_ownership = session_instance_; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::uncallback( const std::string &name_ )
{
    const auto it = _callbacks.find( name_ );

    if( it == _callbacks.end())
        return;

    _callbacks.erase( it );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::deliver( const zen::bones_framework_event_shared &event_ )
{
    if( _sock_fd == -1 )
    {
        std::this_thread::yield();
        std::cout
            << "        deliver: "
            << event_->tag()
            << ", payload: "
            << event_->payload()
            << " @ "
            << _service_dispatcher->name()
            << std::endl;

        auto it = _callbacks.find( event_->tag());
        if( it == _callbacks.end())
        {
            std::cout
                << "no callbacks, event lost"
                << std::endl;
            return;
        }
        _service_dispatcher->enqueue(
            it->second,
            event_
        );
    }
    else
    {
        std::this_thread::yield();
        std::cout
            << "           send: "
            << event_->tag()
            << ", payload: "
            << event_->payload()
            << " @ "
            << _service_dispatcher->name()
            << std::endl;

        size_t header_size = event_->tag().size();
        send(
            _sock_fd,
            &header_size,
            sizeof( header_size ),
            0
        );
        send(
            _sock_fd,
            event_->tag().data(),
            header_size,
            0
        );

        const std::string &payload = event_->payload();
        size_t payload_size = payload.size();
        send(
            _sock_fd,
            &payload_size,
            sizeof( payload_size ),
            0
        );
        send(
            _sock_fd,
            payload.data(),
            payload_size,
            0
        );
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::dispatch(
    const std::string &tag_,
    const std::string &payload_
)
{
    auto dispatched_event = std::make_shared< zen::bones_framework_event >(
        tag_,
        payload_
    );

    dispatch( dispatched_event );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::dispatch( const zen::bones_framework_event_shared &event_ )
{
    std::this_thread::yield();
    std::cout
        << "       dispatch: "
        << event_->tag()
        << ", payload: "
        << event_->payload()
        << " @ "
        << _service_dispatcher->name()
        << std::endl;

    auto entangled_accessor = _entangled.lock();
    if( !entangled_accessor )
    {
        std::cout
            << "entangled not available"
            << std::endl;
        return;
    }
    entangled_accessor->deliver( event_ );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_accessor::dispatcher(
    zen::bones_framework_accessor_shared keep_me_alive_,
    int sock_fd_
)
{
    std::cout
        << "zen::bones_framework_accessor "
        << _name
        << " thread is starting...."
        << std::endl;
    _sock_fd = sock_fd_;
    char *buffer = 0;
    size_t length = 0;

    ///
    auto check_buffer = [
        &buffer,
        &length
    ]( size_t needed )
    {
        if( needed > length )
        {
            delete[] buffer;
            buffer = new char[needed];
            length = needed;
        }
    };

    ///
    while( true )
    { ///
        std::cout
            << "zen::bones_framework_accessor "
            << _name
            << " thread is waiting...."
            << std::endl;
        size_t header_size;
        if( recv(
            _sock_fd,
            &header_size,
            sizeof( header_size ),
            0
        ) <= 0 )
        {
            break;
        }
        check_buffer( header_size );
        if( recv(
            _sock_fd,
            buffer,
            header_size,
            0
        ) <= 0 )
        {
            break;
        }
        std::string tag(
            buffer,
            header_size
        );

        ///
        size_t payload_size;
        if( recv(
            _sock_fd,
            &payload_size,
            sizeof( payload_size ),
            0
        ) <= 0 )
        {
            break;
        }
        check_buffer( payload_size );
        if( recv(
            _sock_fd,
            buffer,
            payload_size,
            0
        ) <= 0 )
        {
            break;
        }

        ///
        std::cout
            << "zen::bones_framework_accessor "
            << _name
            << " thread is working...."
            << std::endl;
        auto event_received = std::make_shared< zen::bones_framework_event >(
            tag,
            std::string(
                buffer,
                payload_size
            ));

        std::this_thread::yield();
        std::cout
            << "           recv: "
            << event_received->tag()
            << ", payload: "
            << event_received->payload()
            << " @ "
            << _service_dispatcher->name()
            << std::endl;

        keep_me_alive_->dispatch( event_received );
    }

    delete[] buffer;
    std::cout
        << "zen::bones_framework_accessor "
        << _name
        << " thread is stopping...."
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
