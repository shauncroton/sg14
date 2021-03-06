///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/bones/framework/bones_framework_service.hpp>


///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_service::bones_framework_service(
    std::string name_,
    zen::bones_framework_dispatcher_shared dispatcher_
)
    : _name( std::move( name_ ))
    , _dispatcher( std::move( dispatcher_ ))
{
    //zen::bones_framework_service::start( //    dispatcher_,
    //    "framework_view",
    //    zen::bones_framework_service::factory<M, S>
    //);

    std::cout
        << "service "
        << _name
        << " is created"
        << std::endl;
}


///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::bones_framework_service::~bones_framework_service()
{
    _dispatcher->directory()->remove( _name );
    std::cout
        << "service "
        << _name
        << " is destroyed"
        << std::endl;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
