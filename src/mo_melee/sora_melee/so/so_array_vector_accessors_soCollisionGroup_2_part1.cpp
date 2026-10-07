#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>

template s32 soArrayVector<soCollisionGroup, 2>::getTopIndex() const;
template void soArrayVector<soCollisionGroup, 2>::setTopIndex(s32);
template s32 soArrayVector<soCollisionGroup, 2>::getLastIndex() const;
template void soArrayVector<soCollisionGroup, 2>::setLastIndex(s32);
template soCollisionGroup& soArrayVector<soCollisionGroup, 2>::getArrayValueConst(s32);
template void soArrayVector<soCollisionGroup, 2>::onFull();
template void soArrayVector<soCollisionGroup, 2>::offFull();
template bool soArrayVector<soCollisionGroup, 2>::isFull() const;
template s32 soArrayVector<soCollisionGroup, 2>::capacity() const;
template s32 soArrayVector<soCollisionGroup, 2>::size() const;
template void soArrayVector<soCollisionGroup, 2>::setSize(s32);
