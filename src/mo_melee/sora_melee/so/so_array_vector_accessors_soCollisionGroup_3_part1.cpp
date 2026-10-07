#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>

template s32 soArrayVector<soCollisionGroup, 3>::getTopIndex() const;
template void soArrayVector<soCollisionGroup, 3>::setTopIndex(s32);
template s32 soArrayVector<soCollisionGroup, 3>::getLastIndex() const;
template void soArrayVector<soCollisionGroup, 3>::setLastIndex(s32);
template soCollisionGroup& soArrayVector<soCollisionGroup, 3>::getArrayValueConst(s32);
template void soArrayVector<soCollisionGroup, 3>::onFull();
template void soArrayVector<soCollisionGroup, 3>::offFull();
template bool soArrayVector<soCollisionGroup, 3>::isFull() const;
template s32 soArrayVector<soCollisionGroup, 3>::capacity() const;
template s32 soArrayVector<soCollisionGroup, 3>::size() const;
template void soArrayVector<soCollisionGroup, 3>::setSize(s32);
