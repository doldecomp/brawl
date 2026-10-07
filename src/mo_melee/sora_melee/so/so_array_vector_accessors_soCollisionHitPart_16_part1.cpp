#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 16>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 16>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 16>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 16>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 16>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 16>::onFull();
template void soArrayVector<soCollisionHitPart, 16>::offFull();
template bool soArrayVector<soCollisionHitPart, 16>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 16>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 16>::size() const;
template void soArrayVector<soCollisionHitPart, 16>::setSize(s32);
