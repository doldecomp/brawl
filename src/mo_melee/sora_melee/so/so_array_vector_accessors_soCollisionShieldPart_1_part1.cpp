#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 1>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 1>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 1>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 1>::onFull();
template void soArrayVector<soCollisionShieldPart, 1>::offFull();
template bool soArrayVector<soCollisionShieldPart, 1>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 1>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 1>::size() const;
template void soArrayVector<soCollisionShieldPart, 1>::setSize(s32);
