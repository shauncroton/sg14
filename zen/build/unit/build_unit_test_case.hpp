#ifndef __ZEN__BUILD_UNIT_TEST__HPP
#define __ZEN__BUILD_UNIT_TEST__HPP
#if 0
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/build/build_unit.h>
#include <zen/build/build_macros.h>
#include <functional>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class build_unit_test_case
{
    struct feature
    {
        const std::string text_;
        const std::function< void() > callback_;

        template<
            typename T,
            typename C
        >
        feature(
            T text_,
            C callback_
        )
            : _text( text_ )
            , _callback( callback_ )
        {
            return;
        }
    };

    using feature_list_type = std::vector< feature >;

public:

    build_unit_test_case(
        std::string text_,
        feature_list_type feature_list_
    )
        : _text( std::move( text_ ))
        , _features( std::move( features_ ))
    {
        return;
    }

private:

    const std::string _text;
    const feature_list_type _feature_list;
};
#endif
///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__BUILD_UNIT_TEST__HPP
