#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 15>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 15>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 15>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 15>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 15>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 15>::onFull();
template void soArrayVector<soCollisionShieldPart, 15>::offFull();
template bool soArrayVector<soCollisionShieldPart, 15>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 15>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 15>::size() const;
template void soArrayVector<soCollisionShieldPart, 15>::setSize(s32);
