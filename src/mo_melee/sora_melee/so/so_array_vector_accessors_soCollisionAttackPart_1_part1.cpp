#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 1>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 1>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 1>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 1>::onFull();
template void soArrayVector<soCollisionAttackPart, 1>::offFull();
template bool soArrayVector<soCollisionAttackPart, 1>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 1>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 1>::size() const;
template void soArrayVector<soCollisionAttackPart, 1>::setSize(s32);
