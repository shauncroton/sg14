#ifndef __ZEN__PARTS__DATA__H
#define __ZEN__PARTS__DATA__H

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#include <types.h>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
namespace zen
{
    class parts_data_journal;

    using parts_data_journal_shared =
    types< parts_data_journal >::shared;

    class parts_data_tree;

    using parts_data_tree_shared =
    types< parts_data_tree >::shared;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///
#endif // __ZEN__PARTS__DATA__H
