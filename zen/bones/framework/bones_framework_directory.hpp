#ifndef __ZEN__BONES_FRAMEWORK_DIRECTORY__HPP
#define __ZEN__BONES_FRAMEWORK_DIRECTORY__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/bones_framework.h>
#include <unordered_map>
#include <thread>
#include <mutex>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::bones_framework_directory
{
    using service_map_type =
    std::unordered_map<
        std::string,
        zen::bones_framework_acceptor_shared
    >;

    bones_framework_directory( const bones_framework_directory & ) = delete;

    bones_framework_directory &
    operator=( bones_framework_directory ) = delete;

    bones_framework_directory( bones_framework_directory && ) = delete;

    bones_framework_directory &
    operator=( bones_framework_directory && ) = delete;

public:

    ~bones_framework_directory();

    explicit bones_framework_directory( std::string name_ );

    const std::string &
    name() const
    { return _name; }

    void
    insert(
        const std::string &name_,
        const zen::bones_framework_acceptor_shared &acceptor_
    );

    void
    remove( const std::string &name_ );

    zen::bones_framework_acceptor_shared
    lookup( const std::string &name_ );

    void
    clear();

private:

    const std::string _name;

    std::mutex _service_map_mutex;
    service_map_type _service_map;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK_DIRECTORY__HPP
