#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_capacity
#define SO_ARRAY_LIST_EXTERNAL_getArrayIndex
#define SO_ARRAY_LIST_EXTERNAL_insertSub
#define SO_ARRAY_LIST_EXTERNAL_eraseSub
#include <so/so_array.h>
class BaseItem;

template BaseItem*& soArrayList<BaseItem*, 64>::at(s32);
template BaseItem* const& soArrayList<BaseItem*, 64>::at(s32) const;
template void soArrayList<BaseItem*, 64>::unshift(BaseItem* const&);
template void soArrayList<BaseItem*, 64>::shift();
template void soArrayList<BaseItem*, 64>::pop();
template void soArrayList<BaseItem*, 64>::insert(s32,BaseItem* const&);
template bool soArrayList<BaseItem*, 64>::isFull() const;
template void soArrayList<BaseItem*, 64>::set(s32,BaseItem* const&,s32);
template bool soArrayList<BaseItem*, 64>::isNull() const;
template s32 soArrayList<BaseItem*, 64>::shiftFreeArrayIndex(s32);
