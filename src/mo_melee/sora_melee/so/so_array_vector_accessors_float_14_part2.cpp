#pragma force_active on
#include <so/so_array.h>

template void soArrayVector<float, 14>::setTopIndex(s32);
template void soArrayVector<float, 14>::setLastIndex(s32);
template float& soArrayVector<float, 14>::getArrayValueConst(s32);
template void soArrayVector<float, 14>::onFull();
template void soArrayVector<float, 14>::offFull();
template s32 soArrayVector<float, 14>::size() const;
template float& soArrayVector<float, 14>::atFastAbstractSub(s32) const;
template void soArrayVector<float, 14>::setSize(s32);
