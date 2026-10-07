#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template void soArrayVector<soCollisionHitPart, 3>::setTopIndex(s32);
template void soArrayVector<soCollisionHitPart, 3>::setLastIndex(s32);
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 3>::getArrayValueConst(s32);
template void soArrayVector<soCollisionHitPart, 3>::onFull();
template void soArrayVector<soCollisionHitPart, 3>::offFull();
template soCollisionHitPart& soArrayVector<soCollisionHitPart, 3>::atFastAbstractSub(s32) const;
template void soArrayVector<soCollisionHitPart, 3>::setSize(s32);
