#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_QUERY_MEMBERS
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_capacity
#define SO_ARRAY_LIST_EXTERNAL_isFull
#define SO_ARRAY_LIST_EXTERNAL_shiftFreeArrayIndex
#include <so/so_array.h>
class itFigureArchive;

template void soArrayList<itFigureArchive*, 64>::push(itFigureArchive* const&);
template void soArrayList<itFigureArchive*, 64>::erase(s32);
template void soArrayList<itFigureArchive*, 64>::clear();
template s32 soArrayList<itFigureArchive*, 64>::getArrayIndex(s32) const;
template s32 soArrayList<itFigureArchive*, 64>::insertSub(s32,s32);
template void soArrayList<itFigureArchive*, 64>::eraseSub(s32);
