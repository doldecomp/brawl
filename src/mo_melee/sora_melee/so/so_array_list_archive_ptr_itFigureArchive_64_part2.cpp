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
class itFigureArchive;

template itFigureArchive*& soArrayList<itFigureArchive*, 64>::at(s32);
template itFigureArchive* const& soArrayList<itFigureArchive*, 64>::at(s32) const;
template void soArrayList<itFigureArchive*, 64>::unshift(itFigureArchive* const&);
template void soArrayList<itFigureArchive*, 64>::shift();
template void soArrayList<itFigureArchive*, 64>::pop();
template void soArrayList<itFigureArchive*, 64>::insert(s32,itFigureArchive* const&);
