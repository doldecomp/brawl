#pragma force_active on
#include <so/so_array.h>

template void soArrayVector<float, 6>::setTopIndex(s32);
template void soArrayVector<float, 6>::setLastIndex(s32);
template float& soArrayVector<float, 6>::getArrayValueConst(s32);
template void soArrayVector<float, 6>::onFull();
template void soArrayVector<float, 6>::offFull();
template s32 soArrayVector<float, 6>::size() const;
template float& soArrayVector<float, 6>::atFastAbstractSub(s32) const;
template void soArrayVector<float, 6>::setSize(s32);
