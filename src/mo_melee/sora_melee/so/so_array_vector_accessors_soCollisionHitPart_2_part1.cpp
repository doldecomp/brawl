#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 2>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 2>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 2>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 2>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 2>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 2>::onFull();
template void soArrayVector<soCollisionHitPart, 2>::offFull();
template bool soArrayVector<soCollisionHitPart, 2>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 2>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 2>::size() const;
template void soArrayVector<soCollisionHitPart, 2>::setSize(s32);
