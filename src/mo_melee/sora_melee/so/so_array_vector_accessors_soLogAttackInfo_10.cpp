#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLogAttackInfo.h>

template bool soArrayVector<soLogAttackInfo, 10>::isFull() const;
template s32 soArrayVector<soLogAttackInfo, 10>::size() const;
template s32 soArrayVector<soLogAttackInfo, 10>::getTopIndex() const;
template void soArrayVector<soLogAttackInfo, 10>::setTopIndex(s32);
template s32 soArrayVector<soLogAttackInfo, 10>::getLastIndex() const;
template void soArrayVector<soLogAttackInfo, 10>::setLastIndex(s32);
template soLogAttackInfo& soArrayVector<soLogAttackInfo, 10>::getArrayValueConst(s32);
template void soArrayVector<soLogAttackInfo, 10>::onFull();
template void soArrayVector<soLogAttackInfo, 10>::offFull();
template s32 soArrayVector<soLogAttackInfo, 10>::capacity() const;
template soLogAttackInfo& soArrayVector<soLogAttackInfo, 10>::atFastAbstractSub(s32) const;
template void soArrayVector<soLogAttackInfo, 10>::setSize(s32);
