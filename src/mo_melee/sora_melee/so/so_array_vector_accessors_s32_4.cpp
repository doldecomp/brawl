#pragma force_active on
#include <so/so_array.h>

template bool soArrayVector<s32, 4>::isFull() const;
template s32 soArrayVector<s32, 4>::size() const;
template s32 soArrayVector<s32, 4>::getTopIndex() const;
template void soArrayVector<s32, 4>::setTopIndex(s32);
template s32 soArrayVector<s32, 4>::getLastIndex() const;
template void soArrayVector<s32, 4>::setLastIndex(s32);
template s32& soArrayVector<s32, 4>::getArrayValueConst(s32);
template void soArrayVector<s32, 4>::onFull();
template void soArrayVector<s32, 4>::offFull();
template s32 soArrayVector<s32, 4>::capacity() const;
template s32& soArrayVector<s32, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<s32, 4>::setSize(s32);
