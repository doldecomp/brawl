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

template itArchive*& soArrayList<itArchive*, 128>::at(s32);
template itArchive* const& soArrayList<itArchive*, 128>::at(s32) const;
template void soArrayList<itArchive*, 128>::unshift(itArchive* const&);
template void soArrayList<itArchive*, 128>::shift();
template void soArrayList<itArchive*, 128>::pop();
template void soArrayList<itArchive*, 128>::insert(s32,itArchive* const&);
