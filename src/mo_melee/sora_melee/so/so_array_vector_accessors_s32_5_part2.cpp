#pragma force_active on
#include <so/so_array.h>

template void soArrayVector<s32, 5>::setTopIndex(s32);
template void soArrayVector<s32, 5>::setLastIndex(s32);
template s32& soArrayVector<s32, 5>::getArrayValueConst(s32);
template void soArrayVector<s32, 5>::onFull();
template void soArrayVector<s32, 5>::offFull();
template s32 soArrayVector<s32, 5>::size() const;
template s32& soArrayVector<s32, 5>::atFastAbstractSub(s32) const;
template void soArrayVector<s32, 5>::setSize(s32);
