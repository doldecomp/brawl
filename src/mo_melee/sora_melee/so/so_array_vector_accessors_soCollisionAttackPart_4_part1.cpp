#pragma force_active on
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>

template s32 soArrayVector<soCollisionAttackPart, 4>::getTopIndex() const;
template void soArrayVector<soCollisionAttackPart, 4>::setTopIndex(s32);
template s32 soArrayVector<soCollisionAttackPart, 4>::getLastIndex() const;
template void soArrayVector<soCollisionAttackPart, 4>::setLastIndex(s32);
template soCollisionAttackPart& soArrayVector<soCollisionAttackPart, 4>::getArrayValueConst(s32);
template void soArrayVector<soCollisionAttackPart, 4>::onFull();
template void soArrayVector<soCollisionAttackPart, 4>::offFull();
template bool soArrayVector<soCollisionAttackPart, 4>::isFull() const;
template s32 soArrayVector<soCollisionAttackPart, 4>::capacity() const;
template s32 soArrayVector<soCollisionAttackPart, 4>::size() const;
template void soArrayVector<soCollisionAttackPart, 4>::setSize(s32);
