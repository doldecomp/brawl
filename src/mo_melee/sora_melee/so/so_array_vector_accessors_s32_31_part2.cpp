#pragma force_active on
#include <so/so_array.h>

template void soArrayVector<s32, 31>::setTopIndex(s32);
template void soArrayVector<s32, 31>::setLastIndex(s32);
template s32& soArrayVector<s32, 31>::getArrayValueConst(s32);
template void soArrayVector<s32, 31>::onFull();
template void soArrayVector<s32, 31>::offFull();
template s32 soArrayVector<s32, 31>::size() const;
template s32& soArrayVector<s32, 31>::atFastAbstractSub(s32) const;
template void soArrayVector<s32, 31>::setSize(s32);
