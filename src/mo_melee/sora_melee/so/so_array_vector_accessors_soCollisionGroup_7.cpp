#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>

template s32 soArrayVector<soCollisionGroup, 7>::getTopIndex() const;
template void soArrayVector<soCollisionGroup, 7>::setTopIndex(s32);
template s32 soArrayVector<soCollisionGroup, 7>::getLastIndex() const;
template void soArrayVector<soCollisionGroup, 7>::setLastIndex(s32);
template soCollisionGroup& soArrayVector<soCollisionGroup, 7>::getArrayValueConst(s32);
template void soArrayVector<soCollisionGroup, 7>::onFull();
template void soArrayVector<soCollisionGroup, 7>::offFull();
template bool soArrayVector<soCollisionGroup, 7>::isFull() const;
template s32 soArrayVector<soCollisionGroup, 7>::capacity() const;
template s32 soArrayVector<soCollisionGroup, 7>::size() const;
template soCollisionGroup& soArrayVector<soCollisionGroup, 7>::atFastAbstractSub(s32) const;
template void soArrayVector<soCollisionGroup, 7>::setSize(s32);
