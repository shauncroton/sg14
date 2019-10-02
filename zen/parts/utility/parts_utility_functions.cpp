///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/utility/parts_utility_functions.hpp>
#include <utility>
#include <stdexcept>
#include <algorithm>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::ltrim( std::string &s_ )
{
    s_.erase(
        s_.begin(),
        std::find_if(
            s_.begin(),
            s_.end(),
            []( int ch )
            {
                return !std::isspace( ch );
            }
        ));
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::rtrim( std::string &s_ )
{
    s_.erase(
        std::find_if(
            s_.rbegin(),
            s_.rend(),
            []( int ch )
            {
                return !std::isspace( ch );
            }
        ).base(),
        s_.end());
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::trim( std::string &s_ )
{
    ltrim( s_ );
    rtrim( s_ );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
zen::ltrim_copy( std::string s_ )
{
    ltrim( s_ );
    return s_;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
zen::rtrim_copy( std::string s_ )
{
    rtrim( s_ );
    return s_;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
zen::trim_copy( std::string s_ )
{
    trim( s_ );
    return s_;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::split(
    const std::string &value_,
    char splitter_,
    std::string &left_,
    std::string &right_
)
{
    auto split_point = value_.find( splitter_ );
    left_ = value_.substr(
        0,
        split_point
    );
    right_ = split_point == std::string::npos
        ? std::string()
        : value_.substr( split_point + 1 );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace
{
    std::string
    get_user( const std::string &connection_string_ )
    {
        const auto number_found = std::count(
            connection_string_.begin(),
            connection_string_.end(),
            '@'
        );

        if( number_found == 0 )
        {
            return "";
        }

        if( number_found > 1 )
            throw std::runtime_error( "invalid destination string" );

        auto it_end = connection_string_.find( '@' );
        auto it_other = connection_string_.find( ':' );
        if( it_end > it_other )
            throw std::runtime_error( "invalid destination string" );

        return connection_string_.substr(
            0,
            it_end
        );
    }

    std::string
    get_host( const std::string &connection_string_ )
    {
        const auto number_found = std::count(
            connection_string_.begin(),
            connection_string_.end(),
            ':'
        );

        if( number_found > 1 )
            throw std::runtime_error( "invalid destination string" );

        auto it_begin = connection_string_.find( '@' );
        if( it_begin == std::string::npos )
        {
            it_begin = 0;
        }
        else
        {
            ++it_begin;
        }

        auto it_end = connection_string_.find( ':' );

        if( it_begin == it_end )
        {
            return "localhost";
        }

        return connection_string_.substr(
            it_begin,
            it_end - it_begin
        );
    }

    uint16_t
    get_port( const std::string &connection_string_ )
    {
        auto it_begin = connection_string_.find( ':' );
        if( it_begin == std::string::npos )
        {
            return 0;
        }

        const auto port = std::stoi(
            connection_string_.substr(
                ++it_begin
            ));

        if( port != uint16_t( port ))
            throw std::runtime_error( "port out of range" );

        return uint16_t( port );
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::network_connection_string::network_connection_string(
    const std::string &connection_string_
)
    : _user( get_user( connection_string_ ))
    , _host( get_host( connection_string_ ))
    , _port( get_port( connection_string_ ))
{
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::registry_path_tokens::registry_path_tokens(
    const std::string &registry_path_
)
{
    for( size_t begin_idx = 0, end_idx; begin_idx != std::string::npos; begin_idx = end_idx )
    {
        end_idx = registry_path_.find(
            '/',
            ++begin_idx
        );

        _tokens.emplace_back(
            registry_path_.substr(
                begin_idx,
                end_idx - begin_idx
            ));
    }

    auto it = _tokens.end();

    _value = *( --it );
    _key = *( --it );
    _op = _value[ 0 ];
    _value.erase(
        0,
        1
    );
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
