#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soCollisionAttackAbsolute.h>

template s32 soArrayVector<soCollisionAttackAbsolute, 10>::getTopIndex() const;
template void soArrayVector<soCollisionAttackAbsolute, 10>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackAbsolute, 10>::getLastIndex() const;
template void soArrayVector<soCollisionAttackAbsolute, 10>::setLastIndex(s32);
template soCollisionAttackAbsolute& soArrayVector<soCollisionAttackAbsolute, 10>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackAbsolute, 10>::onFull();
template void soArrayVector<soCollisionAttackAbsolute, 10>::offFull();
template bool soArrayVector<soCollisionAttackAbsolute, 10>::isFull() const;
template s32 soArrayVector<soCollisionAttackAbsolute, 10>::capacity() const;
template s32 soArrayVector<soCollisionAttackAbsolute, 10>::size() const;
template void soArrayVector<soCollisionAttackAbsolute, 10>::setSize(s32);
