#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 8>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 8>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 8>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 8>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 8>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 8>::onFull();
template void soArrayVector<soCollisionAttackPart, 8>::offFull();
template bool soArrayVector<soCollisionAttackPart, 8>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 8>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 8>::size() const;
template void soArrayVector<soCollisionAttackPart, 8>::setSize(s32);
