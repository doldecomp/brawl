#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template s32 soArrayVector<soCollisionShieldPart, 2>::getTopIndex() const;
template void soArrayVector<soCollisionShieldPart, 2>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldPart, 2>::getLastIndex() const;
template void soArrayVector<soCollisionShieldPart, 2>::setLastIndex(s32);
template soCollisionShieldPart& soArrayVector<soCollisionShieldPart, 2>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldPart, 2>::onFull();
template void soArrayVector<soCollisionShieldPart, 2>::offFull();
template bool soArrayVector<soCollisionShieldPart, 2>::isFull() const;
template s32 soArrayVector<soCollisionShieldPart, 2>::capacity() const;
template s32 soArrayVector<soCollisionShieldPart, 2>::size() const;
template void soArrayVector<soCollisionShieldPart, 2>::setSize(s32);
