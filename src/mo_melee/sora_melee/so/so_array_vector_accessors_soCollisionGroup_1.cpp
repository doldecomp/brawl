#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>

template s32 soArrayVector<soCollisionGroup, 1>::size() const;
template s32 soArrayVector<soCollisionGroup, 1>::getTopIndex() const;
template void soArrayVector<soCollisionGroup, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionGroup, 1>::getLastIndex() const;
template void soArrayVector<soCollisionGroup, 1>::setLastIndex(s32);
template soCollisionGroup& soArrayVector<soCollisionGroup, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionGroup, 1>::onFull();
template void soArrayVector<soCollisionGroup, 1>::offFull();
template bool soArrayVector<soCollisionGroup, 1>::isFull() const;
template s32 soArrayVector<soCollisionGroup, 1>::capacity() const;
template soCollisionGroup& soArrayVector<soCollisionGroup, 1>::atFastAbstractSub(s32) const;
template void soArrayVector<soCollisionGroup, 1>::setSize(s32);
