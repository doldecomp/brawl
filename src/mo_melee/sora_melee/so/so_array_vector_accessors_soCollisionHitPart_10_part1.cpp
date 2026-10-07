#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 10>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 10>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 10>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 10>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 10>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 10>::onFull();
template void soArrayVector<soCollisionHitPart, 10>::offFull();
template bool soArrayVector<soCollisionHitPart, 10>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 10>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 10>::size() const;
template void soArrayVector<soCollisionHitPart, 10>::setSize(s32);
