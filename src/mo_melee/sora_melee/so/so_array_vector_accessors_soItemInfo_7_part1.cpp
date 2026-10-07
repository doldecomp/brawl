#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soItemInfo.h>

template s32 soArrayVector<soItemInfo, 7>::getTopIndex() const;
template void soArrayVector<soItemInfo, 7>::setTopIndex(s32);
template s32 soArrayVector<soItemInfo, 7>::getLastIndex() const;
template void soArrayVector<soItemInfo, 7>::setLastIndex(s32);
template soItemInfo& soArrayVector<soItemInfo, 7>::getArrayValueConst(s32);
template void soArrayVector<soItemInfo, 7>::onFull();
template void soArrayVector<soItemInfo, 7>::offFull();
template bool soArrayVector<soItemInfo, 7>::isFull() const;
template s32 soArrayVector<soItemInfo, 7>::capacity() const;
template s32 soArrayVector<soItemInfo, 7>::size() const;
template void soArrayVector<soItemInfo, 7>::setSize(s32);
