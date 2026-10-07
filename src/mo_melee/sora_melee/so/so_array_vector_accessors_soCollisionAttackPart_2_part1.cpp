#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 2>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 2>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 2>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 2>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 2>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 2>::onFull();
template void soArrayVector<soCollisionAttackPart, 2>::offFull();
template bool soArrayVector<soCollisionAttackPart, 2>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 2>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 2>::size() const;
template void soArrayVector<soCollisionAttackPart, 2>::setSize(s32);
