#pragma force_active on
#include <revolution/gx.h>
#include <so/collision/so_collision_catch_part.h>

template soCollisionCatchPart& soArrayVectorAbstract<soCollisionCatchPart>::at(s32);
template const soCollisionCatchPart& soArrayVectorAbstract<soCollisionCatchPart>::at(s32) const;
template void soArrayVectorAbstract<soCollisionCatchPart>::unshift(const soCollisionCatchPart&);
template void soArrayVectorAbstract<soCollisionCatchPart>::shift();
template void soArrayVectorAbstract<soCollisionCatchPart>::push(const soCollisionCatchPart&);
template void soArrayVectorAbstract<soCollisionCatchPart>::pop();
template void soArrayVectorAbstract<soCollisionCatchPart>::insert(s32, const soCollisionCatchPart&);
template void soArrayVectorAbstract<soCollisionCatchPart>::erase(s32);
template void soArrayVectorAbstract<soCollisionCatchPart>::set(s32, const soCollisionCatchPart&, s32);
template void soArrayVectorAbstract<soCollisionCatchPart>::clear();
template bool soArrayVectorAbstract<soCollisionCatchPart>::isNull() const;
template void soArrayVectorAbstract<soCollisionCatchPart>::substitution(s32, s32);
