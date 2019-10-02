#ifndef __ZEN__BUILD_MACROS__H
#define __ZEN__BUILD_MACROS__H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>
#include <stdexcept>
#include <string>
#include <typeinfo>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#define __S1__( M ) #M                                                                            \

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#define __S2__( M ) __S1__( M )                                                                   \

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#define FAILURE( M )                                                                              \
  std::logic_error(                                                                               \
    std::string( typeid(this).name() ) +                                                          \
    "::" +                                                                                        \
    __func__  +                                                                                   \
    " @ " __FILE__ "(" __S2__(__LINE__) ") "                                                      \
    "[" __S1__( M ) "]"                                                                           \
  )                                                                                               \

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#define MATCHES( M, L, R )                                                                        \
    do                                                                                            \
    {                                                                                             \
        if( !( ( L ) == ( R ) ) )  throw FAILURE( L == R );                                       \
    }                                                                                             \
    while( false )                                                                                \

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#define DIFFERS( M, L, R )                                                                        \
    do                                                                                            \
    {                                                                                             \
        if( ( L ) == ( R ) )  throw FAILURE( L == R );                                            \
    }                                                                                             \
    while( false )                                                                                \

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#define CATCHES( M, X, E, W )                                                                     \
    do                                                                                            \
    {                                                                                             \
        try                                                                                       \
        {                                                                                         \
            X;                                                                                    \
            FAILURE( __S2__( E ) " not thrown" );                                                 \
        }                                                                                         \
        catch( const E &e )                                                                       \
        {                                                                                         \
            MATCHES( M, std::string( W ), e.what());                                              \
        }                                                                                         \
        catch( const std::exception &e )                                                          \
        {                                                                                         \
            throw FAILURE( std::string( "Unexpected std::exception thrown  -- " ) + e.what());    \
        }                                                                                         \
        catch( ... )                                                                              \
        {                                                                                         \
            throw FAILURE( std::string( "Unexpected non std::exception thrown" ));                \
        }                                                                                         \
    }                                                                                             \
    while( false )                                                                                \
        
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_MACROS__H
