#pragma force_active on
#include <revolution/gx.h>
#include <so/collision/so_collision_search_part.h>

template soCollisionSearchPart& soArrayVectorAbstract<soCollisionSearchPart>::at(s32);
template const soCollisionSearchPart& soArrayVectorAbstract<soCollisionSearchPart>::at(s32) const;
template void soArrayVectorAbstract<soCollisionSearchPart>::unshift(const soCollisionSearchPart&);
template void soArrayVectorAbstract<soCollisionSearchPart>::shift();
template void soArrayVectorAbstract<soCollisionSearchPart>::push(const soCollisionSearchPart&);
template void soArrayVectorAbstract<soCollisionSearchPart>::pop();
template void soArrayVectorAbstract<soCollisionSearchPart>::insert(s32, const soCollisionSearchPart&);
template void soArrayVectorAbstract<soCollisionSearchPart>::erase(s32);
template void soArrayVectorAbstract<soCollisionSearchPart>::set(s32, const soCollisionSearchPart&, s32);
template void soArrayVectorAbstract<soCollisionSearchPart>::clear();
template bool soArrayVectorAbstract<soCollisionSearchPart>::isNull() const;
template void soArrayVectorAbstract<soCollisionSearchPart>::substitution(s32, s32);
