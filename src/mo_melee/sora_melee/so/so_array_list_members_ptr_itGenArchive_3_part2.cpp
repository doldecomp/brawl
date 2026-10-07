#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_capacity
#define SO_ARRAY_LIST_EXTERNAL_getArrayIndex
#define SO_ARRAY_LIST_EXTERNAL_insertSub
#define SO_ARRAY_LIST_EXTERNAL_eraseSub
#include <so/so_array.h>
class itGenArchive;

template itGenArchive*& soArrayList<itGenArchive*, 3>::at(s32);
template itGenArchive* const& soArrayList<itGenArchive*, 3>::at(s32) const;
template void soArrayList<itGenArchive*, 3>::unshift(itGenArchive* const&);
template void soArrayList<itGenArchive*, 3>::shift();
template void soArrayList<itGenArchive*, 3>::pop();
template void soArrayList<itGenArchive*, 3>::insert(s32,itGenArchive* const&);
template bool soArrayList<itGenArchive*, 3>::isFull() const;
template void soArrayList<itGenArchive*, 3>::set(s32,itGenArchive* const&,s32);
template bool soArrayList<itGenArchive*, 3>::isNull() const;
template s32 soArrayList<itGenArchive*, 3>::shiftFreeArrayIndex(s32);
