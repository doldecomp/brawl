#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soItemInfo.h>

template s32 soArrayVector<soItemInfo, 3>::getTopIndex() const;
template void soArrayVector<soItemInfo, 3>::setTopIndex(s32);
template s32 soArrayVector<soItemInfo, 3>::getLastIndex() const;
template void soArrayVector<soItemInfo, 3>::setLastIndex(s32);
template soItemInfo& soArrayVector<soItemInfo, 3>::getArrayValueConst(s32);
template void soArrayVector<soItemInfo, 3>::onFull();
template void soArrayVector<soItemInfo, 3>::offFull();
template bool soArrayVector<soItemInfo, 3>::isFull() const;
template s32 soArrayVector<soItemInfo, 3>::capacity() const;
template s32 soArrayVector<soItemInfo, 3>::size() const;
template void soArrayVector<soItemInfo, 3>::setSize(s32);
