///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/framework/bones_framework_directory.hpp>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///

zen::bones_framework_directory::bones_framework_directory(
    std::string name_
)
    : _name( std::move( name_ ))
{
    std::cout << "directory " << _name << " is created" << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///

zen::bones_framework_directory::~bones_framework_directory()
{
    std::cout << "directory " << _name << " is destroyed" << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_directory::insert(
    const std::string &name_,
    const zen::bones_framework_acceptor_shared &acceptor_
)
{
    std::lock_guard< std::mutex > g( _service_map_mutex );
    _service_map[ name_ ] = acceptor_;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_directory::remove(
    const std::string &name_
)
{
    std::lock_guard< std::mutex > g( _service_map_mutex );
    auto it = _service_map.find( name_ );
    if( it == _service_map.end())
        return;
    _service_map.erase( it );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_acceptor_shared
zen::bones_framework_directory::lookup(
    const std::string &name_
)
{
    std::lock_guard< std::mutex > g( _service_map_mutex );
    auto it = _service_map.find( name_ );
    if( it == _service_map.end())
    {
        return zen::bones_framework_acceptor_shared();
    }
    return it->second;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::bones_framework_directory::remove_all()
{
    std::lock_guard< std::mutex > g( _service_map_mutex );
    _service_map.clear();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
const std::string &
zen::bones_framework_directory::get_name() const
{
    return _name;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
