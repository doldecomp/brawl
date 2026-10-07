#pragma force_active on
#include <so/so_array.h>
class BaseItem;

template s32 soArrayVector<BaseItem*, 1>::getTopIndex() const;
template void soArrayVector<BaseItem*, 1>::setTopIndex(s32);
template s32 soArrayVector<BaseItem*, 1>::getLastIndex() const;
template void soArrayVector<BaseItem*, 1>::setLastIndex(s32);
template BaseItem*& soArrayVector<BaseItem*, 1>::getArrayValueConst(s32);
template void soArrayVector<BaseItem*, 1>::onFull();
template void soArrayVector<BaseItem*, 1>::offFull();
template bool soArrayVector<BaseItem*, 1>::isFull() const;
template s32 soArrayVector<BaseItem*, 1>::capacity() const;
template s32 soArrayVector<BaseItem*, 1>::size() const;
template BaseItem*& soArrayVector<BaseItem*, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<BaseItem*, 1>::setSize(s32);
