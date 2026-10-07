#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_catch_part.h>

template s32 soArrayVector<soCollisionCatchPart, 2>::getTopIndex() const;
template void soArrayVector<soCollisionCatchPart, 2>::setTopIndex(s32);
template s32 soArrayVector<soCollisionCatchPart, 2>::getLastIndex() const;
template void soArrayVector<soCollisionCatchPart, 2>::setLastIndex(s32);
template soCollisionCatchPart& soArrayVector<soCollisionCatchPart, 2>::getArrayValueConst(s32);
template void soArrayVector<soCollisionCatchPart, 2>::onFull();
template void soArrayVector<soCollisionCatchPart, 2>::offFull();
template bool soArrayVector<soCollisionCatchPart, 2>::isFull() const;
template s32 soArrayVector<soCollisionCatchPart, 2>::capacity() const;
template s32 soArrayVector<soCollisionCatchPart, 2>::size() const;
template void soArrayVector<soCollisionCatchPart, 2>::setSize(s32);
