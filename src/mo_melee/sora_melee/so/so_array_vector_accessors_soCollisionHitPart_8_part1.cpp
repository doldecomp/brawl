#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 8>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 8>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 8>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 8>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 8>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 8>::onFull();
template void soArrayVector<soCollisionHitPart, 8>::offFull();
template bool soArrayVector<soCollisionHitPart, 8>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 8>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 8>::size() const;
template void soArrayVector<soCollisionHitPart, 8>::setSize(s32);
