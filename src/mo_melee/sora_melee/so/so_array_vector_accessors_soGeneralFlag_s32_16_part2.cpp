#pragma force_active on
#include <so/so_array.h>

template void soArrayVector<soGeneralFlag<s32>, 16>::setTopIndex(s32);
template void soArrayVector<soGeneralFlag<s32>, 16>::setLastIndex(s32);
template soGeneralFlag<s32>& soArrayVector<soGeneralFlag<s32>, 16>::getArrayValueConst(s32);
template void soArrayVector<soGeneralFlag<s32>, 16>::onFull();
template void soArrayVector<soGeneralFlag<s32>, 16>::offFull();
template s32 soArrayVector<soGeneralFlag<s32>, 16>::size() const;
template soGeneralFlag<s32>& soArrayVector<soGeneralFlag<s32>, 16>::atFastAbstractSub(s32) const;
template void soArrayVector<soGeneralFlag<s32>, 16>::setSize(s32);
