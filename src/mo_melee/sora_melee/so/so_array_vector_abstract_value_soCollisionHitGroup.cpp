#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_hit_group.h>


template soCollisionHitGroup& soArrayVectorAbstract<soCollisionHitGroup>::at(s32);
template const soCollisionHitGroup& soArrayVectorAbstract<soCollisionHitGroup>::at(s32) const;
template void soArrayVectorAbstract<soCollisionHitGroup>::unshift(const soCollisionHitGroup&);
template void soArrayVectorAbstract<soCollisionHitGroup>::shift();
template void soArrayVectorAbstract<soCollisionHitGroup>::push(const soCollisionHitGroup&);
template void soArrayVectorAbstract<soCollisionHitGroup>::pop();
template void soArrayVectorAbstract<soCollisionHitGroup>::insert(s32, const soCollisionHitGroup&);
template void soArrayVectorAbstract<soCollisionHitGroup>::erase(s32);
template void soArrayVectorAbstract<soCollisionHitGroup>::set(s32, const soCollisionHitGroup&, s32);
template void soArrayVectorAbstract<soCollisionHitGroup>::clear();
template bool soArrayVectorAbstract<soCollisionHitGroup>::isNull() const;
template void soArrayVectorAbstract<soCollisionHitGroup>::substitution(s32, s32);
