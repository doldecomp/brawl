#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_INDEX_MEMBERS
#define SO_ARRAY_LIST_EXTERNAL_QUERY_MEMBERS
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_capacity
#define SO_ARRAY_LIST_EXTERNAL_isFull
#define SO_ARRAY_LIST_EXTERNAL_shiftFreeArrayIndex
#define SO_ARRAY_LIST_EXTERNAL_getArrayIndex
#define SO_ARRAY_LIST_EXTERNAL_insertSub
#define SO_ARRAY_LIST_EXTERNAL_eraseSub
#include <so/so_array.h>
class itArchive;

template void soArrayList<itArchive*, 128>::push(itArchive* const&);
template void soArrayList<itArchive*, 128>::erase(s32);
