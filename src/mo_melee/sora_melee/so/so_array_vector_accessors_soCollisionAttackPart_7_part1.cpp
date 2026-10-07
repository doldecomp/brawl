#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 7>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 7>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 7>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 7>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 7>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 7>::onFull();
template void soArrayVector<soCollisionAttackPart, 7>::offFull();
template bool soArrayVector<soCollisionAttackPart, 7>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 7>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 7>::size() const;
template void soArrayVector<soCollisionAttackPart, 7>::setSize(s32);
