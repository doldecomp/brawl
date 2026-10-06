#pragma force_active on
#include <revolution/gx.h>
#include <so/collision/so_collision_shield_part.h>

template soCollisionShieldPart& soArrayVectorAbstract<soCollisionShieldPart>::at(s32);
template const soCollisionShieldPart& soArrayVectorAbstract<soCollisionShieldPart>::at(s32) const;
template void soArrayVectorAbstract<soCollisionShieldPart>::unshift(const soCollisionShieldPart&);
template void soArrayVectorAbstract<soCollisionShieldPart>::shift();
template void soArrayVectorAbstract<soCollisionShieldPart>::push(const soCollisionShieldPart&);
template void soArrayVectorAbstract<soCollisionShieldPart>::pop();
template void soArrayVectorAbstract<soCollisionShieldPart>::insert(s32, const soCollisionShieldPart&);
template void soArrayVectorAbstract<soCollisionShieldPart>::erase(s32);
template void soArrayVectorAbstract<soCollisionShieldPart>::set(s32, const soCollisionShieldPart&, s32);
template void soArrayVectorAbstract<soCollisionShieldPart>::clear();
template bool soArrayVectorAbstract<soCollisionShieldPart>::isNull() const;
template void soArrayVectorAbstract<soCollisionShieldPart>::substitution(s32, s32);
