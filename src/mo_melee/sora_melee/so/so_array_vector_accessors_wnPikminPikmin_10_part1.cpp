#pragma force_active on
#include <so/so_array.h>
class wnPikminPikmin;

template s32 soArrayVector<wnPikminPikmin*, 10>::getTopIndex() const;
template void soArrayVector<wnPikminPikmin*, 10>::setTopIndex(s32);
template s32 soArrayVector<wnPikminPikmin*, 10>::getLastIndex() const;
template void soArrayVector<wnPikminPikmin*, 10>::setLastIndex(s32);
template wnPikminPikmin*& soArrayVector<wnPikminPikmin*, 10>::getArrayValueConst(s32);
template void soArrayVector<wnPikminPikmin*, 10>::onFull();
template void soArrayVector<wnPikminPikmin*, 10>::offFull();
template bool soArrayVector<wnPikminPikmin*, 10>::isFull() const;
template s32 soArrayVector<wnPikminPikmin*, 10>::capacity() const;
template s32 soArrayVector<wnPikminPikmin*, 10>::size() const;
template void soArrayVector<wnPikminPikmin*, 10>::setSize(s32);
