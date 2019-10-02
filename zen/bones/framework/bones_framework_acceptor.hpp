#ifndef __ZEN__BONES_FRAMEWORK_ACCEPTOR__HPP
#define __ZEN__BONES_FRAMEWORK_ACCEPTOR__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <functional>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <future>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::bones_framework_acceptor
{
public: //SCTP

    using session_factory_function = std::function<
        zen::bones_framework_session_shared(
            const zen::bones_framework_accessor_shared &
        )
    >;

    bones_framework_acceptor( const bones_framework_acceptor & ) = delete;

    bones_framework_acceptor &
    operator=( bones_framework_acceptor & ) = delete;

    bones_framework_acceptor( bones_framework_acceptor && ) = delete;

    bones_framework_acceptor &
    operator=( bones_framework_acceptor && ) = delete;

public:

    ~bones_framework_acceptor();

    bones_framework_acceptor(
        zen::bones_framework_dispatcher_shared dispatcher_,
        std::string name_,
        session_factory_function factory_
    );

    zen::bones_framework_accessor_shared
    grant(
        zen::bones_framework_dispatcher_shared &dispatcher_,
        const std::string &name_
    );

    const std::string &
    get_name() const
    {
        return _name;
    }

private:

    void
    listener(
        std::string address,
        zen::bones_framework_acceptor *listener_bones_framework_acceptor,
        std::promise< void > start_thread
    );

private:

    const std::string _name;

    session_factory_function _factory_function;
    std::thread _listener_thread;
    int _sock_fd{ -1 };
    zen::bones_framework_dispatcher_shared _service_dispatcher{ nullptr };
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_ACCEPTOR__HPP
