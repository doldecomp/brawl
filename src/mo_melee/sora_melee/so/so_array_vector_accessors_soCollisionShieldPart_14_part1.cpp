#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 14>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 14>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 14>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 14>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 14>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 14>::onFull();
template void soArrayVector<soCollisionShieldPart, 14>::offFull();
template bool soArrayVector<soCollisionShieldPart, 14>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 14>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 14>::size() const;
template void soArrayVector<soCollisionShieldPart, 14>::setSize(s32);
