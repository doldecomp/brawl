#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soCollisionAttackAbsolute.h>

template s32 soArrayVector<soCollisionAttackAbsolute, 6>::getTopIndex() const;
template void soArrayVector<soCollisionAttackAbsolute, 6>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackAbsolute, 6>::getLastIndex() const;
template void soArrayVector<soCollisionAttackAbsolute, 6>::setLastIndex(s32);
template soCollisionAttackAbsolute& soArrayVector<soCollisionAttackAbsolute, 6>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackAbsolute, 6>::onFull();
template void soArrayVector<soCollisionAttackAbsolute, 6>::offFull();
template bool soArrayVector<soCollisionAttackAbsolute, 6>::isFull() const;
template s32 soArrayVector<soCollisionAttackAbsolute, 6>::capacity() const;
template s32 soArrayVector<soCollisionAttackAbsolute, 6>::size() const;
template void soArrayVector<soCollisionAttackAbsolute, 6>::setSize(s32);
