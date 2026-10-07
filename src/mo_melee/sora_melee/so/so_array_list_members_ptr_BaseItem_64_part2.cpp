#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_isFull
#define SO_ARRAY_LIST_EXTERNAL_shiftFreeArrayIndex
#include <so/so_array.h>
class BaseItem;

template void soArrayList<BaseItem*, 64>::push(BaseItem* const&);
template void soArrayList<BaseItem*, 64>::erase(s32);
template void soArrayList<BaseItem*, 64>::clear();
template s32 soArrayList<BaseItem*, 64>::capacity() const;
template s32 soArrayList<BaseItem*, 64>::getArrayIndex(s32) const;
template s32 soArrayList<BaseItem*, 64>::insertSub(s32,s32);
template void soArrayList<BaseItem*, 64>::eraseSub(s32);
