#ifndef __ZEN__PARTS_UTILITY_H
#define __ZEN__PARTS_UTILITY_H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace zen
{
    void
    ltrim( std::string &s_ );

    void
    rtrim( std::string &s_ );

    void
    trim( std::string &s_ );

    std::string
    ltrim_copy( std::string s_ );

    std::string
    rtrim_copy( std::string s_ );

    std::string
    trim_copy( std::string s_ );

    void
    split(
        const std::string &value_,
        char splitter_,
        std::string &left_,
        std::string &right_
    );

    class network_connection_string;

    class registry_path_tokens;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS_UTILITY_H
