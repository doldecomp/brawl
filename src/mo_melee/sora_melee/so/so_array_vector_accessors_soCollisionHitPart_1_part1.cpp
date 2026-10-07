#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 1>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 1>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 1>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 1>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 1>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 1>::onFull();
template void soArrayVector<soCollisionHitPart, 1>::offFull();
template bool soArrayVector<soCollisionHitPart, 1>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 1>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 1>::size() const;
template void soArrayVector<soCollisionHitPart, 1>::setSize(s32);
