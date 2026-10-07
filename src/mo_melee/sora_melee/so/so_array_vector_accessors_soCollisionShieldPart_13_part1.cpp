#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 13>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 13>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 13>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 13>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 13>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 13>::onFull();
template void soArrayVector<soCollisionShieldPart, 13>::offFull();
template bool soArrayVector<soCollisionShieldPart, 13>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 13>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 13>::size() const;
template void soArrayVector<soCollisionShieldPart, 13>::setSize(s32);
