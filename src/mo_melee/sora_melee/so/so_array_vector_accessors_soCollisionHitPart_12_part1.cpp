#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 12>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 12>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 12>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 12>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 12>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 12>::onFull();
template void soArrayVector<soCollisionHitPart, 12>::offFull();
template bool soArrayVector<soCollisionHitPart, 12>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 12>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 12>::size() const;
template void soArrayVector<soCollisionHitPart, 12>::setSize(s32);
