#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soSlopeStatusParam.h>

template s32 soArrayVector<soSlopeStatusParam, 1>::getTopIndex() const;
template void soArrayVector<soSlopeStatusParam, 1>::setTopIndex(s32);
template s32 soArrayVector<soSlopeStatusParam, 1>::getLastIndex() const;
template void soArrayVector<soSlopeStatusParam, 1>::setLastIndex(s32);
template soSlopeStatusParam& soArrayVector<soSlopeStatusParam, 1>::getArrayValueConst(s32);
template void soArrayVector<soSlopeStatusParam, 1>::onFull();
template void soArrayVector<soSlopeStatusParam, 1>::offFull();
template bool soArrayVector<soSlopeStatusParam, 1>::isFull() const;
template s32 soArrayVector<soSlopeStatusParam, 1>::capacity() const;
template s32 soArrayVector<soSlopeStatusParam, 1>::size() const;
template soSlopeStatusParam& soArrayVector<soSlopeStatusParam, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soSlopeStatusParam, 1>::setSize(s32);
