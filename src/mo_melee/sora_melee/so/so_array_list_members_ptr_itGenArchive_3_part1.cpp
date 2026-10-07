#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_isFull
#define SO_ARRAY_LIST_EXTERNAL_shiftFreeArrayIndex
#include <so/so_array.h>
class itGenArchive;

template void soArrayList<itGenArchive*, 3>::push(itGenArchive* const&);
template void soArrayList<itGenArchive*, 3>::erase(s32);
template s32 soArrayList<itGenArchive*, 3>::size() const;
template void soArrayList<itGenArchive*, 3>::clear();
template s32 soArrayList<itGenArchive*, 3>::capacity() const;
template s32 soArrayList<itGenArchive*, 3>::getArrayIndex(s32) const;
template s32 soArrayList<itGenArchive*, 3>::insertSub(s32,s32);
template void soArrayList<itGenArchive*, 3>::eraseSub(s32);
