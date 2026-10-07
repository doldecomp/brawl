#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_shield_group.h>

template s32 soArrayVector<soCollisionShieldGroup, 4>::getTopIndex() const;
template void soArrayVector<soCollisionShieldGroup, 4>::setTopIndex(s32);
template s32 soArrayVector<soCollisionShieldGroup, 4>::getLastIndex() const;
template void soArrayVector<soCollisionShieldGroup, 4>::setLastIndex(s32);
template soCollisionShieldGroup& soArrayVector<soCollisionShieldGroup, 4>::getArrayValueConst(s32);
template void soArrayVector<soCollisionShieldGroup, 4>::onFull();
template void soArrayVector<soCollisionShieldGroup, 4>::offFull();
template bool soArrayVector<soCollisionShieldGroup, 4>::isFull() const;
template s32 soArrayVector<soCollisionShieldGroup, 4>::capacity() const;
template s32 soArrayVector<soCollisionShieldGroup, 4>::size() const;
template void soArrayVector<soCollisionShieldGroup, 4>::setSize(s32);
