///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/data/parts_data_tree.hpp>
#include <zen/parts/parts_utility.hpp>
#include <vector>
#include <sstream>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::parts_data_tree::parts_data_tree(
    const std::string &str
)
{
    std::vector< parts_data_tree * > stack{ this };
    size_t index = 0;

    std::string key, val, *ptr = &key;
    auto multi_line{ false };

    auto is_triple_quote = []( auto &it )
    {
        return ( *( it + 1 ) == '"' ) && ( *( it + 2 ) == '"' ) && ( *( it + 3 ) == '"' ) && ( *( it + 4 ) == '\n' );
    };

    for( auto it = str.begin(); it != str.end(); ++it )
    {
        if( multi_line )
        {
            ptr->append(
                1,
                *it
            );

            if( is_triple_quote( it ))
            {
                multi_line = false;
                it = it + 3;
            }

            continue;
        }

        switch( *it )
        {
            case '\n':
            {
                trim( key );
                trim( val );
                zen::parts_data_tree &dt = *stack[ index ];
                dt[ key ].set( val );
                stack.erase(
                    stack.begin() + index + 1,
                    stack.end());
                stack.push_back( &dt[ key ] );
                index = 0;
                key.clear();
                val.clear();
                ptr = &key;
                break;
            }
            case '\t':
            {
                ++index;
                break;
            }
            case '=':
            {
                ptr = &val;
                if( is_triple_quote( it ))
                {
                    multi_line = true;
                    it = it + 4;
                }
                break;
            }
            default:
            {
                ptr->append(
                    1,
                    *it
                );
            }
        }
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace
{
    void
    serialize(
        std::ostringstream &oss,
        const zen::parts_data_tree &parts_data_tree_,
        const size_t tab_count
    )
    {
        for( const auto &kv_pair : parts_data_tree_ )
        {
            const auto &key = kv_pair.first;
            const auto &tree = kv_pair.second;
            const auto &val = tree.get();

            std::string tabs(
                tab_count,
                '\t'
            );

            if( val.find_first_of( "=\n\t\0\"" ) == std::string::npos )
            {
                oss << tabs << key << "=" << val << "\n";
            }
            else
            {
                oss << tabs << key << "=\"\"\"\n" << val << "\n\"\"\"\n";
            }

            serialize(
                oss,
                tree,
                tab_count + 1
            );
        }
    };

}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::string
zen::parts_data_tree::str() const
{
    std::ostringstream oss;

    serialize(
        oss,
        *this,
        0
    );

    return oss.str();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
