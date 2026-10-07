#pragma force_active on
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_catch_part.h>

template s32 soArrayVector<soCollisionCatchPart, 4>::getTopIndex() const;
template void soArrayVector<soCollisionCatchPart, 4>::setTopIndex(s32);
template s32 soArrayVector<soCollisionCatchPart, 4>::getLastIndex() const;
template void soArrayVector<soCollisionCatchPart, 4>::setLastIndex(s32);
template soCollisionCatchPart& soArrayVector<soCollisionCatchPart, 4>::getArrayValueConst(s32);
template void soArrayVector<soCollisionCatchPart, 4>::onFull();
template void soArrayVector<soCollisionCatchPart, 4>::offFull();
template bool soArrayVector<soCollisionCatchPart, 4>::isFull() const;
template s32 soArrayVector<soCollisionCatchPart, 4>::capacity() const;
template s32 soArrayVector<soCollisionCatchPart, 4>::size() const;
template void soArrayVector<soCollisionCatchPart, 4>::setSize(s32);
