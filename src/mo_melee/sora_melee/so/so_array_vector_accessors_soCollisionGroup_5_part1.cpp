#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>

template s32 soArrayVector<soCollisionGroup, 5>::getTopIndex() const;
template void soArrayVector<soCollisionGroup, 5>::setTopIndex(s32);
template s32 soArrayVector<soCollisionGroup, 5>::getLastIndex() const;
template void soArrayVector<soCollisionGroup, 5>::setLastIndex(s32);
template soCollisionGroup& soArrayVector<soCollisionGroup, 5>::getArrayValueConst(s32);
template void soArrayVector<soCollisionGroup, 5>::onFull();
template void soArrayVector<soCollisionGroup, 5>::offFull();
template bool soArrayVector<soCollisionGroup, 5>::isFull() const;
template s32 soArrayVector<soCollisionGroup, 5>::capacity() const;
template s32 soArrayVector<soCollisionGroup, 5>::size() const;
template void soArrayVector<soCollisionGroup, 5>::setSize(s32);
