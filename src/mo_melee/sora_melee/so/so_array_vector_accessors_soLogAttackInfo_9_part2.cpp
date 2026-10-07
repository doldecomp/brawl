#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLogAttackInfo.h>

template s32 soArrayVector<soLogAttackInfo, 9>::getTopIndex() const;
template void soArrayVector<soLogAttackInfo, 9>::setTopIndex(s32);
template s32 soArrayVector<soLogAttackInfo, 9>::getLastIndex() const;
template void soArrayVector<soLogAttackInfo, 9>::setLastIndex(s32);
template soLogAttackInfo& soArrayVector<soLogAttackInfo, 9>::getArrayValueConst(s32);
template void soArrayVector<soLogAttackInfo, 9>::onFull();
template void soArrayVector<soLogAttackInfo, 9>::offFull();
template s32 soArrayVector<soLogAttackInfo, 9>::capacity() const;
template soLogAttackInfo& soArrayVector<soLogAttackInfo, 9>::atFastAbstractSub(s32) const;
template void soArrayVector<soLogAttackInfo, 9>::setSize(s32);
