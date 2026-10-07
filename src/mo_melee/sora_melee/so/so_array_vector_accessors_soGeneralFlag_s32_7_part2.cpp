#pragma force_active on
#include <so/so_array.h>

template void soArrayVector<soGeneralFlag<s32>, 7>::setTopIndex(s32);
template void soArrayVector<soGeneralFlag<s32>, 7>::setLastIndex(s32);
template soGeneralFlag<s32>& soArrayVector<soGeneralFlag<s32>, 7>::getArrayValueConst(s32);
template void soArrayVector<soGeneralFlag<s32>, 7>::onFull();
template void soArrayVector<soGeneralFlag<s32>, 7>::offFull();
template s32 soArrayVector<soGeneralFlag<s32>, 7>::size() const;
template soGeneralFlag<s32>& soArrayVector<soGeneralFlag<s32>, 7>::atFastAbstractSub(s32) const;
template void soArrayVector<soGeneralFlag<s32>, 7>::setSize(s32);
