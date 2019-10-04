#ifndef __ZEN__BONES_FRAMEWORK__HPP
#define __ZEN__BONES_FRAMEWORK__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/framework/bones_framework_connection.hpp>
#include <zen/bones/framework/bones_framework_directory.hpp>
#include <zen/bones/framework/bones_framework_service.hpp>
#include <zen/bones/framework/bones_framework_session.hpp>
#include <zen/bones/framework/bones_framework_dispatcher.hpp>
#include <zen/bones/framework/bones_framework_event.hpp>
#include <zen/bones/framework/bones_framework_acceptor.hpp>
#include <zen/bones/framework/bones_framework_accessor.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<
    typename Type,
    typename ...Args
>
inline
std::shared_ptr< Type >
make( Args ...args )
{
    return std::make_shared< Type >( std::forward< Args >( args )... );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BONES_FRAMEWORK__HPP
