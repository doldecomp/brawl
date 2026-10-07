#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_QUERY_MEMBERS
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_capacity
#define SO_ARRAY_LIST_EXTERNAL_isFull
#define SO_ARRAY_LIST_EXTERNAL_shiftFreeArrayIndex
#include <so/so_array.h>
class itArchive;

template s32 soArrayList<itArchive*, 128>::getArrayIndex(s32) const;
template s32 soArrayList<itArchive*, 128>::insertSub(s32,s32);
template void soArrayList<itArchive*, 128>::eraseSub(s32);
