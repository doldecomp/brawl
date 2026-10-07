#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soCollisionAttackAbsolute.h>

template s32 soArrayVector<soCollisionAttackAbsolute, 1>::getTopIndex() const;
template void soArrayVector<soCollisionAttackAbsolute, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackAbsolute, 1>::getLastIndex() const;
template void soArrayVector<soCollisionAttackAbsolute, 1>::setLastIndex(s32);
template soCollisionAttackAbsolute& soArrayVector<soCollisionAttackAbsolute, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackAbsolute, 1>::onFull();
template void soArrayVector<soCollisionAttackAbsolute, 1>::offFull();
template bool soArrayVector<soCollisionAttackAbsolute, 1>::isFull() const;
template s32 soArrayVector<soCollisionAttackAbsolute, 1>::capacity() const;
template s32 soArrayVector<soCollisionAttackAbsolute, 1>::size() const;
template void soArrayVector<soCollisionAttackAbsolute, 1>::setSize(s32);
