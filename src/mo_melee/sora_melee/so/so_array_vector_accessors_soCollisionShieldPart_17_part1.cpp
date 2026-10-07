#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 17>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 17>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 17>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 17>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 17>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 17>::onFull();
template void soArrayVector<soCollisionShieldPart, 17>::offFull();
template bool soArrayVector<soCollisionShieldPart, 17>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 17>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 17>::size() const;
template void soArrayVector<soCollisionShieldPart, 17>::setSize(s32);
