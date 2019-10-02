#ifndef __ZEN__PARTS__TRAITS__HPP
#define __ZEN__PARTS__TRAITS__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/parts_traits.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
template< typename type >
struct zen::parts_traits
{ //    struct unique
//        : public std::unique_ptr< type >
//    { //        template< typename Args... >
//        unique( Args ...args)

//            : std::unique_ptr( std::make_shared< type >
    ( std::forward( args)))
//        { //            return;
//        };
//    };

//    struct shared
//        : public std::shared_ptr< type >
//    { //        template< typename Args... >
//        shared( Args ...args)

//            : std::shared_ptr( std::make_shared< type >
    ( std::forward( args)))
//        { //            return;
//        };
//    };};
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS__TRAITS__HPP
