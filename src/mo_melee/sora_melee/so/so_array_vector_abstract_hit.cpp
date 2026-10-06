#pragma force_active on
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>

template soCollisionHitPart& soArrayVectorAbstract<soCollisionHitPart>::at(s32);
template const soCollisionHitPart& soArrayVectorAbstract<soCollisionHitPart>::at(s32) const;
template void soArrayVectorAbstract<soCollisionHitPart>::unshift(const soCollisionHitPart&);
template void soArrayVectorAbstract<soCollisionHitPart>::shift();
template void soArrayVectorAbstract<soCollisionHitPart>::push(const soCollisionHitPart&);
template void soArrayVectorAbstract<soCollisionHitPart>::pop();
template void soArrayVectorAbstract<soCollisionHitPart>::insert(s32, const soCollisionHitPart&);
template void soArrayVectorAbstract<soCollisionHitPart>::erase(s32);
template void soArrayVectorAbstract<soCollisionHitPart>::set(s32, const soCollisionHitPart&, s32);
template void soArrayVectorAbstract<soCollisionHitPart>::clear();
template bool soArrayVectorAbstract<soCollisionHitPart>::isNull() const;
template void soArrayVectorAbstract<soCollisionHitPart>::substitution(s32, s32);
