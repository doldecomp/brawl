#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_collision_shield_group.h>


template soCollisionShieldGroup& soArrayVectorAbstract<soCollisionShieldGroup>::at(s32);
template const soCollisionShieldGroup& soArrayVectorAbstract<soCollisionShieldGroup>::at(s32) const;
template void soArrayVectorAbstract<soCollisionShieldGroup>::unshift(const soCollisionShieldGroup&);
template void soArrayVectorAbstract<soCollisionShieldGroup>::shift();
template void soArrayVectorAbstract<soCollisionShieldGroup>::push(const soCollisionShieldGroup&);
template void soArrayVectorAbstract<soCollisionShieldGroup>::pop();
template void soArrayVectorAbstract<soCollisionShieldGroup>::insert(s32, const soCollisionShieldGroup&);
template void soArrayVectorAbstract<soCollisionShieldGroup>::erase(s32);
template void soArrayVectorAbstract<soCollisionShieldGroup>::set(s32, const soCollisionShieldGroup&, s32);
template void soArrayVectorAbstract<soCollisionShieldGroup>::clear();
template bool soArrayVectorAbstract<soCollisionShieldGroup>::isNull() const;
template void soArrayVectorAbstract<soCollisionShieldGroup>::substitution(s32, s32);
