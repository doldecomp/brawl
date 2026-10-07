#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<u32, 1>::getTopIndex() const;
template void soArrayVector<u32, 1>::setTopIndex(s32);
template s32 soArrayVector<u32, 1>::getLastIndex() const;
template void soArrayVector<u32, 1>::setLastIndex(s32);
template u32& soArrayVector<u32, 1>::getArrayValueConst(s32);
template void soArrayVector<u32, 1>::onFull();
template void soArrayVector<u32, 1>::offFull();
template bool soArrayVector<u32, 1>::isFull() const;
template s32 soArrayVector<u32, 1>::capacity() const;
template s32 soArrayVector<u32, 1>::size() const;
template u32& soArrayVector<u32, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<u32, 1>::setSize(s32);
