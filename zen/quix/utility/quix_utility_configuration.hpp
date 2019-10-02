#ifndef __ZEN__QUIX_UTILITY_CONFIGURATION__HPP
#define __ZEN__QUIX_UTILITY_CONFIGURATION__HPP
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/quix/quix_utility.h>
#include <vector>
#include <utility>
#include <stdexcept>
#include <cctype>
#include <string>
#include <istream>
#include <iostream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::quix_utility_configuration
{
    struct impl;
    impl *pimpl;

public:

    using key_type =
    std::string;
    using value_type =
    std::string;
    using stream =
    std::istream;

    quix_utility_configuration(
        int,
        char *[]
    );

    quix_utility_configuration( const std::string & );

    quix_utility_configuration( stream && );

    quix_utility_configuration( const quix_utility_configuration & );

    quix_utility_configuration( quix_utility_configuration && );

    quix_utility_configuration &
    operator=( quix_utility_configuration );

    quix_utility_configuration &
    operator=( quix_utility_configuration && );

    ~quix_utility_configuration();

    const value_type &
    operator[]( const key_type & );

    template< typename T >
    T
    get( const key_type & );

    auto
    begin() const;

    auto
    end() const;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename T >
T
zen::quix_utility_configuration::get( const key_type &key_arg )
{ return ( *this )[ key_arg ]; }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline const char *
zen::quix_utility_configuration::get< const char * >( const key_type &key_arg )
{ return ( *this )[ key_arg ].c_str(); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline int
zen::quix_utility_configuration::get< int >( const key_type &key_arg )
{ return std::atoi(( *this )[ key_arg ].c_str()); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline unsigned int
zen::quix_utility_configuration::get< unsigned int >( const key_type &key_arg )
{ return get< int >( key_arg ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline unsigned short
zen::quix_utility_configuration::get< unsigned short >( const key_type &key_arg )
{ return get< int >( key_arg ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline std::size_t
zen::quix_utility_configuration::get< std::size_t >( const key_type &key_arg )
{ return get< int >( key_arg ); }

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline std::vector< unsigned int >
zen::quix_utility_configuration::get< std::vector< unsigned int > >( const key_type &key_arg )
{
    std::vector< unsigned int > vec;
    unsigned int v = 0;
    bool commit = false;
    for( const char d : ( *this )[ key_arg ] )
    {
        if( std::isdigit( d ))
        {
            commit = true;
            v = ( v * 10 ) + ( d - '0' );
            continue;
        }

        if( d == ',' )
        {
            //if( commit ) std::cout << "for " << key_arg << "=" << ( *this )[ key_arg ] << " push_back( " << v << " )\n";
            if( commit )
                vec.push_back( v );
            v = 0;
            commit = false;
            continue;
        }

        if( std::isblank( d ))
        {
            continue;
        }

        throw std::logic_error( "Invalid quix_utility_configuration file entry" );
    }

    //if( commit ) std::cout << "for " << key_arg << "=" << ( *this )[ key_arg ] << " push_back( " << v << " )\n";
    if( commit )
        vec.push_back( v );
    return vec;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template<>
inline std::vector<
    std::pair<
        unsigned int,
        unsigned int
    >
>
zen::quix_utility_configuration::get<
    std::vector<
        std::pair<
            unsigned int,
            unsigned int
        >
    >
>( const key_type &key_arg )
{
    std::vector<
        std::pair<
            unsigned int,
            unsigned int
        >
    > vec;
    unsigned int i = 0, v[2] = {
        0,
        0
    };
    bool commit = false;
    for( const char d : ( *this )[ key_arg ] )
    {
        if( std::isdigit( d ))
        {
            commit = true;
            v[ i ] = ( v[ i ] * 10 ) + ( d - '0' );
            continue;
        }

        if( d == '.' && !i )
        {
            i = !i;
            continue;
        }

        if( d == ',' && i )
        {
            i = !i;
            //if( commit ) std::cout << "for " << key_arg << "=" << ( *this )[ key_arg ] << " push_back( { " << v[0] << ", " << v[1] << "} )\n";
            if( commit )
                vec.push_back(
                    std::make_pair(
                        v[ 0 ],
                        v[ 1 ]
                    ));
            v[ 0 ] = v[ 1 ] = 0;
            commit = false;
            continue;
        }

        if( std::isblank( d ))
        {
            continue;
        }

        throw std::logic_error( "Invalid quix_utility_configuration file entry" );
    }
    //if( commit ) std::cout << "for " << key_arg << "=" << ( *this )[ key_arg ] << " push_back( { " << v[0] << ", " << v[1] << "} )\n";
    if( commit )
        vec.

            push_back(
            std::make_pair(
                v[ 0 ],
                v[ 1 ]
            ));

    return

        vec;
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__QUIX_UTILITY_CONFIGURATION__HPP
