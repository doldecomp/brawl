#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soItemInfo.h>

template s32 soArrayVector<soItemInfo, 4>::getTopIndex() const;
template void soArrayVector<soItemInfo, 4>::setTopIndex(s32);
template s32 soArrayVector<soItemInfo, 4>::getLastIndex() const;
template void soArrayVector<soItemInfo, 4>::setLastIndex(s32);
template soItemInfo& soArrayVector<soItemInfo, 4>::getArrayValueConst(s32);
template void soArrayVector<soItemInfo, 4>::onFull();
template void soArrayVector<soItemInfo, 4>::offFull();
template bool soArrayVector<soItemInfo, 4>::isFull() const;
template s32 soArrayVector<soItemInfo, 4>::capacity() const;
template s32 soArrayVector<soItemInfo, 4>::size() const;
template void soArrayVector<soItemInfo, 4>::setSize(s32);
