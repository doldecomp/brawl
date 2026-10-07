#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 13>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 13>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 13>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 13>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 13>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 13>::onFull();
template void soArrayVector<soCollisionHitPart, 13>::offFull();
template bool soArrayVector<soCollisionHitPart, 13>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 13>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 13>::size() const;
template void soArrayVector<soCollisionHitPart, 13>::setSize(s32);
