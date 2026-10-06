#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_group.h>


template soCollisionGroup& soArrayVectorAbstract<soCollisionGroup>::at(s32);
template const soCollisionGroup& soArrayVectorAbstract<soCollisionGroup>::at(s32) const;
template void soArrayVectorAbstract<soCollisionGroup>::unshift(const soCollisionGroup&);
template void soArrayVectorAbstract<soCollisionGroup>::shift();
template void soArrayVectorAbstract<soCollisionGroup>::push(const soCollisionGroup&);
template void soArrayVectorAbstract<soCollisionGroup>::pop();
template void soArrayVectorAbstract<soCollisionGroup>::insert(s32, const soCollisionGroup&);
template void soArrayVectorAbstract<soCollisionGroup>::erase(s32);
template void soArrayVectorAbstract<soCollisionGroup>::set(s32, const soCollisionGroup&, s32);
template void soArrayVectorAbstract<soCollisionGroup>::clear();
template bool soArrayVectorAbstract<soCollisionGroup>::isNull() const;
template void soArrayVectorAbstract<soCollisionGroup>::substitution(s32, s32);
