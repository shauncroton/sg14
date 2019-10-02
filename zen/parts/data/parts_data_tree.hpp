#ifndef __ZEN__PARTS_DATA_TREE__HPP
#define __ZEN__PARTS_DATA_TREE__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/parts_data.h>
#include <map>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::parts_data_tree
    : public std::map<
        std::string,
        zen::parts_data_tree
    >
{
public:

    parts_data_tree( const parts_data_tree & ) = default;

    parts_data_tree &
    operator=( parts_data_tree & ) = default;

    parts_data_tree( parts_data_tree && ) = default;

    parts_data_tree &
    operator=( parts_data_tree && ) = default;

    ~parts_data_tree() = default;

    parts_data_tree() = default;

    explicit parts_data_tree(
        const std::string &str
    );

    std::string
    str() const;

    void
    set( const std::string &value_ )
    {
        _value = value_;
    }

    const std::string &
    get() const
    {
        return _value;
    }

    const parts_data_tree &
    operator()( const std::string &key_ ) const
    {
        const auto it = this->find( key_ );
        if( it != this->end())
        {
            return it->second;
        }
        static parts_data_tree stub;
        return stub;
    }

private:

    std::string _value;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS_DATA_TREE__HPP