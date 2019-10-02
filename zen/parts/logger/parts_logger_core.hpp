#ifndef __ZEN__PARTS_LOGGER_CORE__HPP
#define __ZEN__PARTS_LOGGER_CORE__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/parts_logger.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::parts_logger_core
{
    parts_logger_core( const parts_logger_core & ) = delete;

    parts_logger_core &
    operator=( parts_logger_core ) = delete;

    parts_logger_core( parts_logger_core && ) = delete;

    parts_logger_core &
    operator=( parts_logger_core && ) = delete;

public:

    ~parts_logger_core() = default;

    parts_logger_core();
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS_LOGGER_CORE__HPP