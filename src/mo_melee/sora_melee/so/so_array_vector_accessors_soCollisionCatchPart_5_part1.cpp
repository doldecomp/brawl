#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_catch_part.h>

template s32 soArrayVector<soCollisionCatchPart, 5>::getTopIndex() const;
template void soArrayVector<soCollisionCatchPart, 5>::setTopIndex(s32);
template s32 soArrayVector<soCollisionCatchPart, 5>::getLastIndex() const;
template void soArrayVector<soCollisionCatchPart, 5>::setLastIndex(s32);
template soCollisionCatchPart& soArrayVector<soCollisionCatchPart, 5>::getArrayValueConst(s32);
template void soArrayVector<soCollisionCatchPart, 5>::onFull();
template void soArrayVector<soCollisionCatchPart, 5>::offFull();
template bool soArrayVector<soCollisionCatchPart, 5>::isFull() const;
template s32 soArrayVector<soCollisionCatchPart, 5>::capacity() const;
template s32 soArrayVector<soCollisionCatchPart, 5>::size() const;
template void soArrayVector<soCollisionCatchPart, 5>::setSize(s32);
