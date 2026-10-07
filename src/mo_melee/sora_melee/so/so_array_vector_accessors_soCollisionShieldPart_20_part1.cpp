#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 20>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 20>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 20>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 20>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 20>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 20>::onFull();
template void soArrayVector<soCollisionShieldPart, 20>::offFull();
template bool soArrayVector<soCollisionShieldPart, 20>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 20>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 20>::size() const;
template void soArrayVector<soCollisionShieldPart, 20>::setSize(s32);
