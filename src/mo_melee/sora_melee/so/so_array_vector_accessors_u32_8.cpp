#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<u32, 8>::size() const;
template s32 soArrayVector<u32, 8>::getTopIndex() const;
template void soArrayVector<u32, 8>::setTopIndex(s32);
template s32 soArrayVector<u32, 8>::getLastIndex() const;
template void soArrayVector<u32, 8>::setLastIndex(s32);
template u32& soArrayVector<u32, 8>::getArrayValueConst(s32);
template void soArrayVector<u32, 8>::onFull();
template void soArrayVector<u32, 8>::offFull();
template bool soArrayVector<u32, 8>::isFull() const;
template s32 soArrayVector<u32, 8>::capacity() const;
template u32& soArrayVector<u32, 8>::atFastAbstractSub(s32) const;
template void soArrayVector<u32, 8>::setSize(s32);
