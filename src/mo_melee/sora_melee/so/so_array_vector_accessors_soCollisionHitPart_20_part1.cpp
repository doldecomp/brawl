#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template s32 soArrayVector<soCollisionHitPart, 20>::getTopIndex() const;
template void soArrayVector<soCollisionHitPart, 20>::setTopIndex(s32);
template s32 soArrayVector<soCollisionHitPart, 20>::getLastIndex() const;
template void soArrayVector<soCollisionHitPart, 20>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 20>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 20>::onFull();
template void soArrayVector<soCollisionHitPart, 20>::offFull();
template bool soArrayVector<soCollisionHitPart, 20>::isFull() const;
template s32 soArrayVector<soCollisionHitPart, 20>::capacity() const;
template s32 soArrayVector<soCollisionHitPart, 20>::size() const;
template void soArrayVector<soCollisionHitPart, 20>::setSize(s32);
