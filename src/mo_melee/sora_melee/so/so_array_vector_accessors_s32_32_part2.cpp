#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<s32, 32>::getTopIndex() const;
template void soArrayVector<s32, 32>::setTopIndex(s32);
template s32 soArrayVector<s32, 32>::getLastIndex() const;
template void soArrayVector<s32, 32>::setLastIndex(s32);
template s32& soArrayVector<s32, 32>::getArrayValueConst(s32);
template void soArrayVector<s32, 32>::onFull();
template void soArrayVector<s32, 32>::offFull();
template bool soArrayVector<s32, 32>::isFull() const;
template s32 soArrayVector<s32, 32>::capacity() const;
template s32& soArrayVector<s32, 32>::atFastAbstractSub(s32) const;
template void soArrayVector<s32, 32>::setSize(s32);
