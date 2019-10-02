#ifndef __ZEN__PARTS_UTILITY_FUNCTIONS__HPP
#define __ZEN__PARTS_UTILITY_FUNCTIONS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/parts_utility.h>
#include <vector>
#include <cstring>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::network_connection_string
{
public:

    ~network_connection_string() = default;

    explicit network_connection_string( const std::string &destination_ );

    const std::string &
    user()
    {
        return _user;
    };

    const std::string &
    host()
    {
        return _host;
    };

    uint16_t
    port()
    {
        return _port;
    };

private:

    const std::string _user;
    const std::string _host;
    const uint16_t _port;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::registry_path_tokens
{
public:

    ~registry_path_tokens() = default;

    explicit registry_path_tokens( const std::string &registry_path_ );

    const std::string &
    operator()( size_t pos_ ) const
    {
        return _tokens.at( pos_ );
    };

    size_t
    size()
    {
        return _tokens.size();
    }

    const std::string &
    key()
    {
        return _key;
    }

    const std::string &
    value()
    {
        return _value;
    }

    char
    op()
    {
        return _op;
    }

private:

    std::vector< std::string > _tokens;
    std::string _key;
    std::string _value;
    char _op{ 0 };
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS_UTILITY_FUNCTIONS__HPP
