#pragma force_active on
#include <so/so_array.h>
class BaseItem;

template s32 soArrayVector<BaseItem*, 10>::getTopIndex() const;
template void soArrayVector<BaseItem*, 10>::setTopIndex(s32);
template s32 soArrayVector<BaseItem*, 10>::getLastIndex() const;
template void soArrayVector<BaseItem*, 10>::setLastIndex(s32);
template BaseItem*& soArrayVector<BaseItem*, 10>::getArrayValueConst(s32);
template void soArrayVector<BaseItem*, 10>::onFull();
template void soArrayVector<BaseItem*, 10>::offFull();
template bool soArrayVector<BaseItem*, 10>::isFull() const;
template s32 soArrayVector<BaseItem*, 10>::capacity() const;
template BaseItem*& soArrayVector<BaseItem*, 10>::atFastAbstractSub(s32) const;
template void soArrayVector<BaseItem*, 10>::setSize(s32);
