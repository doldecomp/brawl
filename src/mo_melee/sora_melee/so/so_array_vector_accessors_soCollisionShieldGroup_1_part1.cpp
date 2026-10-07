#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_shield_group.h>

template s32 soArrayVector<soCollisionShieldGroup, 1>::getTopIndex() const;
template void soArrayVector<soCollisionShieldGroup, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldGroup, 1>::getLastIndex() const;
template void soArrayVector<soCollisionShieldGroup, 1>::setLastIndex(s32);
template soCollisionShieldGroup& soArrayVector<soCollisionShieldGroup, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldGroup, 1>::onFull();
template void soArrayVector<soCollisionShieldGroup, 1>::offFull();
template bool soArrayVector<soCollisionShieldGroup, 1>::isFull() const;
template s32 soArrayVector<soCollisionShieldGroup, 1>::capacity() const;
template s32 soArrayVector<soCollisionShieldGroup, 1>::size() const;
template void soArrayVector<soCollisionShieldGroup, 1>::setSize(s32);
