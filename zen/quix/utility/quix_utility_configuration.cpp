///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/utility/quix_utility_configuration.hpp>
#include <unordered_map>
#include <utility>
#include <istream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace
{
    std::ifstream
    make_ifstream(
        int argc_arg,
        char *argv_arg[]
    )
    {
        std::ifstream stream;
        std::string filename(
            argc_arg == 1
                ? ( std::string( argv_arg[ 0 ] ) + ".cfg" )
                : argc_arg == 2
                ? ( std::string( argv_arg[ 1 ] ))
                : throw std::runtime_error( "invalid command line arguments" ));
        stream.open( filename );
        if( !stream.is_open())
            throw std::runtime_error( "Failed to open quix_utility_configuration file" );

        return stream;
    }
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace
{
    std::string &
    ltrim( std::string &s )
    {
        s.erase(
            s.begin(),
            std::find_if(
                s.begin(),
                s.end(),
                []( int c )
                { return !std::isblank( c ); }
            ));
        return s;
    }
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace
{
    std::string &
    rtrim( std::string &s )
    {
        s.erase(
            std::find_if(
                s.rbegin(),
                s.rend(),
                []( int c )
                { return !std::isblank( c ); }
            ).base(),
            s.end());
        return s;
    }
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct zen::quix_utility_configuration::impl
{
    using dictionary_type =
    std::unordered_map<
        key_type,
        value_type
    >;

    dictionary_type dictionary_mem;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration::quix_utility_configuration(
    int argc_arg,
    char *argv_arg[]
)
    : quix_utility_configuration(
    make_ifstream(
        argc_arg,
        argv_arg
    ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration::quix_utility_configuration( const std::string &string_arg )
    : pimpl( new impl )
{
    std::stringstream stream;
    stream
        << string_arg;

    std::string line;
    while( !getline(
        stream,
        line
    ).eof())
    {
        if( line.empty())
            continue;
        ltrim( rtrim( line ));
        if( line[ 0 ] == '#' )
            continue;
        const auto equals_pos = line.find( "=" );
        if( equals_pos == std::string::npos )
            continue;
        const auto key = line.substr(
            0,
            equals_pos
        );
        const auto value = line.substr( equals_pos + 1 );
        pimpl->dictionary_mem[ key ] = value;
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration::quix_utility_configuration( stream &&stream_arg )
    : pimpl( new impl )
{
    std::string line;
    while( !getline(
        stream_arg,
        line
    ).eof())
    {
        if( line.empty())
            continue;
        ltrim( rtrim( line ));
        if( line[ 0 ] == '#' )
            continue;
        const auto equals_pos = line.find( "=" );
        if( equals_pos == std::string::npos )
            continue;
        const auto key = line.substr(
            0,
            equals_pos
        );
        const auto value = line.substr( equals_pos + 1 );
        pimpl->dictionary_mem[ key ] = value;
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration::quix_utility_configuration( const quix_utility_configuration &other )
    : pimpl( new impl( *other.pimpl ))
{}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration::quix_utility_configuration( quix_utility_configuration &&other )
    : pimpl( other.pimpl )
{ other.pimpl = nullptr; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration &
zen::quix_utility_configuration::operator=( quix_utility_configuration other )
{
    std::swap(
        pimpl,
        other.pimpl
    );
    return *this;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration &
zen::quix_utility_configuration::operator=( quix_utility_configuration &&other )
{
    std::swap(
        pimpl,
        other.pimpl
    );
    return *this;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::quix_utility_configuration::~quix_utility_configuration()
{ delete pimpl; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
const zen::quix_utility_configuration::value_type &
zen::quix_utility_configuration::operator[]( const key_type &key )
{
    const auto it = pimpl->dictionary_mem.find( key );
    if( it != pimpl->dictionary_mem.cend())
    {
        return it->second;
    }

    const auto what = key + " not found in quix_utility_configuration";
    throw ( std::invalid_argument( what ));
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
auto
zen::quix_utility_configuration::begin() const
{ return pimpl->dictionary_mem.begin(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
auto
zen::quix_utility_configuration::end() const
{ return pimpl->dictionary_mem.end(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
to_string( const zen::quix_utility_configuration &quix_utility_configuration_arg )
{
    std::stringstream ss;
    ss
        << "{";
    for( auto pair : quix_utility_configuration_arg )
    {
        const auto &key = pair.first;
        const auto &value = pair.second;
        ss
            << "{\""
            << key
            << "\":\""
            << value
            << "\"}";
    }
    ss
        << "}";
    return ss.str();
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
