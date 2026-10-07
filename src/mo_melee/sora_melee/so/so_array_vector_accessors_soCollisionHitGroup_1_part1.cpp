#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_hit_group.h>

template s32 soArrayVector<soCollisionHitGroup, 1>::getTopIndex() const;
template void soArrayVector<soCollisionHitGroup, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitGroup, 1>::getLastIndex() const;
template void soArrayVector<soCollisionHitGroup, 1>::setLastIndex(s32);
template soCollisionHitGroup& soArrayVector<soCollisionHitGroup, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitGroup, 1>::onFull();
template void soArrayVector<soCollisionHitGroup, 1>::offFull();
template bool soArrayVector<soCollisionHitGroup, 1>::isFull() const;
template s32 soArrayVector<soCollisionHitGroup, 1>::capacity() const;
template s32 soArrayVector<soCollisionHitGroup, 1>::size() const;
template void soArrayVector<soCollisionHitGroup, 1>::setSize(s32);
