#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_shield_group.h>

template s32 soArrayVector<soCollisionShieldGroup, 3>::getTopIndex() const;
template void soArrayVector<soCollisionShieldGroup, 3>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldGroup, 3>::getLastIndex() const;
template void soArrayVector<soCollisionShieldGroup, 3>::setLastIndex(s32);
template soCollisionShieldGroup& soArrayVector<soCollisionShieldGroup, 3>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldGroup, 3>::onFull();
template void soArrayVector<soCollisionShieldGroup, 3>::offFull();
template bool soArrayVector<soCollisionShieldGroup, 3>::isFull() const;
template s32 soArrayVector<soCollisionShieldGroup, 3>::capacity() const;
template s32 soArrayVector<soCollisionShieldGroup, 3>::size() const;
template void soArrayVector<soCollisionShieldGroup, 3>::setSize(s32);
