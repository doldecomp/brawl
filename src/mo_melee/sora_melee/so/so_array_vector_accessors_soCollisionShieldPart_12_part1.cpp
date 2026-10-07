#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 12>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 12>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 12>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 12>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 12>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 12>::onFull();
template void soArrayVector<soCollisionShieldPart, 12>::offFull();
template bool soArrayVector<soCollisionShieldPart, 12>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 12>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 12>::size() const;
template void soArrayVector<soCollisionShieldPart, 12>::setSize(s32);
