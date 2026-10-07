#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 11>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 11>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 11>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 11>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 11>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 11>::onFull();
template void soArrayVector<soCollisionHitPart, 11>::offFull();
template bool soArrayVector<soCollisionHitPart, 11>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 11>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 11>::size() const;
template void soArrayVector<soCollisionHitPart, 11>::setSize(s32);
