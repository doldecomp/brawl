#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 3>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 3>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 3>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 3>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 3>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 3>::onFull();
template void soArrayVector<soCollisionAttackPart, 3>::offFull();
template bool soArrayVector<soCollisionAttackPart, 3>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 3>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 3>::size() const;
template void soArrayVector<soCollisionAttackPart, 3>::setSize(s32);
