///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <zen/parts/data/parts_data_journal.hpp>
#include <zen/parts/parts_utility.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
std::ofstream &
disk()
{
    static std::ofstream persisted(
        "/var/tmp/ops.studio/journal." + std::to_string( syscall( SYS_gettid )) + ".txt",
        std::ios::trunc | std::ios::binary | std::ios::out
    );
    return persisted;
};

std::vector< zen::parts_data_journal::data_buffer * > _rb_ring_[256];

uint8_t _rb_index_{ 0 };

constexpr uint8_t _rb_size_{ 9 };

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
struct zen::parts_data_journal::data_buffer
{
    data_buffer *_old_buff;
    const std::string _buff;
    long _hash{ 0 };
    bool _dirty{ true };

    explicit data_buffer(
        data_buffer *old_buff_,
        std::string buff_
    )
        : _old_buff( old_buff_ )
        , _buff( std::move( buff_ ))
    {
    };
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::parts_data_journal &
zen::parts_data_journal::initialize()
{
    static parts_data_journal journal( nullptr );
    return journal;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::parts_data_journal::rollback( parts_data_journal &node_ )
{
    node_.rollback();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::parts_data_journal::commit(
    parts_data_journal &node_,
    bool ignore_dirty_
)
{
    for( auto buff : _rb_ring_[ ++_rb_index_ ] )
    {
        delete buff->_old_buff;
        buff->_old_buff = nullptr;
    }

    _rb_ring_[ _rb_index_ ].clear();

    const auto old_hash = node_._hash;
    node_.commit( ignore_dirty_ );
    disk() << "{{" << old_hash << "}}\n";
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::parts_data_journal::parts_data_journal(
    parts_data_journal *parent
)
    : _parent( parent )
{
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
void
zen::parts_data_journal::rollback()
{
    for( const auto &pair : _name_to_data_dict )
    {
        auto data = pair.second;
        if( data->_old_buff == nullptr )
            continue; // nothing to rollback for this data
        while( data->_old_buff )
            data = data->_old_buff; // get oldest state remembered

        const auto &name = pair.first;
        set(
            name,
            data->_buff.c_str());
    }

    for( const auto &pair : _name_to_node_dict )
    {
        const auto &node = pair.second;

        node->rollback();
    }
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
long
zen::parts_data_journal::commit( bool ignore_dirty_ ) const
{
    if( !( ignore_dirty_ || _dirty ))
        return _hash;

    std::stringstream ss;

    for( const auto &pair : _name_to_data_dict )
    {
        const auto &name = pair.first;
        const auto &data = pair.second;

        if( data->_dirty )
        {
            data->_hash = disk().tellp();
            disk() << "[[" << data->_buff.size() << "]]\n";
            disk() << data->_buff << "\n";
            data->_dirty = false;
        }

        ss << data->_hash << "=" << name << "\n";
    }

    for( const auto &pair : _name_to_node_dict )
    {
        const auto &name = pair.first;
        const auto &node = pair.second;

        const auto hash = node->commit( ignore_dirty_ );

        ss << hash << ":" << name << "\n";
    }

    _hash = disk().tellp();
    disk() << "[" << ss.str().size() << "]\n";
    disk() << ss.str() << "\n";

    _dirty = false;
    return _hash;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
bool
zen::parts_data_journal::set_dirty() const
{
    return !_dirty && ( _dirty = true ) && _parent->set_dirty();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
const char *
zen::parts_data_journal::get(
    const std::string &name_
) const
{
    auto it = _name_to_data_dict.find( name_ );
    if( it == _name_to_data_dict.end())
        return nullptr;
    const auto &data = ( *it ).second;
    return data->_buff.c_str();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
const char *
zen::parts_data_journal::set(
    const std::string &name_,
    const char *buff_
)
{
    auto data_ptr = _name_to_data_dict[ name_ ];
    data_ptr = new data_type(
        data_ptr,
        buff_
    );
    _rb_ring_[ _rb_index_ + _rb_size_ ].emplace_back( data_ptr );
    _name_to_data_dict[ name_ ] = data_ptr;
    set_dirty();
    return data_ptr->_buff.c_str();
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
zen::parts_data_journal &
zen::parts_data_journal::operator[]( const std::string &name_ )
{
    auto it = _name_to_node_dict.find( name_ );
    if( it == _name_to_node_dict.end())
    {
        it = _name_to_node_dict.emplace(
            name_,
            new node_type( this )).first;
        set_dirty();
    }
    auto &journal = ( *it ).second;
    return *journal;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
const zen::parts_data_journal &
zen::parts_data_journal::operator()( const std::string &name_ ) const
{
    auto it = _name_to_node_dict.find( name_ );
    if( it == _name_to_node_dict.end())
        throw std::runtime_error( "data journal name not found" );
    auto &journal = ( *it ).second;
    return *journal;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
