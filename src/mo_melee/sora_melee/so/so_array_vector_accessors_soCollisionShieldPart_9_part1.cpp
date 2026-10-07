#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 9>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 9>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 9>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 9>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 9>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 9>::onFull();
template void soArrayVector<soCollisionShieldPart, 9>::offFull();
template bool soArrayVector<soCollisionShieldPart, 9>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 9>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 9>::size() const;
template void soArrayVector<soCollisionShieldPart, 9>::setSize(s32);
