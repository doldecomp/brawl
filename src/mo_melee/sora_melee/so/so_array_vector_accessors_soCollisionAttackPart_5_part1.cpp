#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 5>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 5>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 5>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 5>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 5>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 5>::onFull();
template void soArrayVector<soCollisionAttackPart, 5>::offFull();
template bool soArrayVector<soCollisionAttackPart, 5>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 5>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 5>::size() const;
template void soArrayVector<soCollisionAttackPart, 5>::setSize(s32);
