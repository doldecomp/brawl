#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_hit_group.h>

template s32 soArrayVector<soCollisionHitGroup, 3>::getTopIndex() const;
template void soArrayVector<soCollisionHitGroup, 3>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitGroup, 3>::getLastIndex() const;
template void soArrayVector<soCollisionHitGroup, 3>::setLastIndex(s32);
template soCollisionHitGroup& soArrayVector<soCollisionHitGroup, 3>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitGroup, 3>::onFull();
template void soArrayVector<soCollisionHitGroup, 3>::offFull();
template bool soArrayVector<soCollisionHitGroup, 3>::isFull() const;
template s32 soArrayVector<soCollisionHitGroup, 3>::capacity() const;
template s32 soArrayVector<soCollisionHitGroup, 3>::size() const;
template soCollisionHitGroup& soArrayVector<soCollisionHitGroup, 3>::atFastAbstractSub(s32) const;
template void soArrayVector<soCollisionHitGroup, 3>::setSize(s32);
