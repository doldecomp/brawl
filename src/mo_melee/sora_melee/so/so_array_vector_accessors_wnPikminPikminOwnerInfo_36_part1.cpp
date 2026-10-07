#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPikminPikminOwnerInfo.h>

template s32 soArrayVector<wnPikminPikminOwnerInfo, 36>::getTopIndex() const;
template void soArrayVector<wnPikminPikminOwnerInfo, 36>::setTopIndex(s32);
template s32 soArrayVector<wnPikminPikminOwnerInfo, 36>::getLastIndex() const;
template void soArrayVector<wnPikminPikminOwnerInfo, 36>::setLastIndex(s32);
template wnPikminPikminOwnerInfo& soArrayVector<wnPikminPikminOwnerInfo, 36>::getArrayValueConst(s32);
template void soArrayVector<wnPikminPikminOwnerInfo, 36>::onFull();
template void soArrayVector<wnPikminPikminOwnerInfo, 36>::offFull();
template bool soArrayVector<wnPikminPikminOwnerInfo, 36>::isFull() const;
template s32 soArrayVector<wnPikminPikminOwnerInfo, 36>::capacity() const;
template s32 soArrayVector<wnPikminPikminOwnerInfo, 36>::size() const;
template void soArrayVector<wnPikminPikminOwnerInfo, 36>::setSize(s32);
