#ifndef __ZEN__PARTS_DATA_JOURNAL__HPP
#define __ZEN__PARTS_DATA_JOURNAL__HPP

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/parts_data.h>
#include <unordered_map>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
class zen::parts_data_journal
{
    parts_data_journal( const parts_data_journal & ) = default;

    parts_data_journal &
    operator=( parts_data_journal & ) = default;

    parts_data_journal( parts_data_journal && ) = default;

    parts_data_journal &
    operator=( parts_data_journal && ) = default;

    ~parts_data_journal() = default;

    explicit parts_data_journal( parts_data_journal *parent );

public:

    struct data_buffer;

    using name_type =
    std::string;

    using data_type =
    data_buffer;

    using node_type =
    zen::parts_data_journal;

    using name_to_node_dict_type =
    std::unordered_map<
        name_type,
        node_type *
    >;

    using name_to_data_dict_type =
    std::unordered_map<
        name_type,
        data_type *
    >;

    static node_type &
    initialize();

    static void
    rollback( node_type &node_ );

    static void
    commit(
        node_type &node_,
        bool ignore_dirty_ = false
    );

private:

    const char *
    get( const std::string &name_ ) const;

    const char *
    set(
        const std::string &name_,
        const char *buff_
    );

    node_type &
    operator[]( const std::string &name_ );

    const node_type &
    operator()( const std::string &name_ ) const;

private:

    void
    rollback();

    long
    commit( bool ignore_dirty_ ) const;

    bool
    set_dirty() const;

    name_to_data_dict_type _name_to_data_dict;

    name_to_node_dict_type _name_to_node_dict;

    mutable long _hash;

    mutable bool _dirty{ true };

    node_type *_parent;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS_DATA_JOURNAL__HPP
