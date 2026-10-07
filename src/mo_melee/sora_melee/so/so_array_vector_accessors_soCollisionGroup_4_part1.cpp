#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>

template s32 soArrayVector<soCollisionGroup, 4>::getTopIndex() const;
template void soArrayVector<soCollisionGroup, 4>::setTopIndex(s32);
template s32 soArrayVector<soCollisionGroup, 4>::getLastIndex() const;
template void soArrayVector<soCollisionGroup, 4>::setLastIndex(s32);
template soCollisionGroup& soArrayVector<soCollisionGroup, 4>::getArrayValueConst(s32);
template void soArrayVector<soCollisionGroup, 4>::onFull();
template void soArrayVector<soCollisionGroup, 4>::offFull();
template bool soArrayVector<soCollisionGroup, 4>::isFull() const;
template s32 soArrayVector<soCollisionGroup, 4>::capacity() const;
template s32 soArrayVector<soCollisionGroup, 4>::size() const;
template void soArrayVector<soCollisionGroup, 4>::setSize(s32);
