#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<s32, 1>::getTopIndex() const;
template void soArrayVector<s32, 1>::setTopIndex(s32);
template s32 soArrayVector<s32, 1>::getLastIndex() const;
template void soArrayVector<s32, 1>::setLastIndex(s32);
template s32& soArrayVector<s32, 1>::getArrayValueConst(s32);
template void soArrayVector<s32, 1>::onFull();
template void soArrayVector<s32, 1>::offFull();
template bool soArrayVector<s32, 1>::isFull() const;
template s32 soArrayVector<s32, 1>::capacity() const;
template s32 soArrayVector<s32, 1>::size() const;
template void soArrayVector<s32, 1>::setSize(s32);
