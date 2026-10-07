#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<s32, 2>::getTopIndex() const;
template void soArrayVector<s32, 2>::setTopIndex(s32);
template s32 soArrayVector<s32, 2>::getLastIndex() const;
template void soArrayVector<s32, 2>::setLastIndex(s32);
template s32& soArrayVector<s32, 2>::getArrayValueConst(s32);
template void soArrayVector<s32, 2>::onFull();
template void soArrayVector<s32, 2>::offFull();
template bool soArrayVector<s32, 2>::isFull() const;
template s32 soArrayVector<s32, 2>::capacity() const;
template s32 soArrayVector<s32, 2>::size() const;
template void soArrayVector<s32, 2>::setSize(s32);
