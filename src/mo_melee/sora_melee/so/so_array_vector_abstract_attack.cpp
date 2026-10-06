#pragma force_active on
#include <so/collision/templates/so_collision_attack_part.h>

template soCollisionAttackPart& soArrayVectorAbstract<soCollisionAttackPart>::at(s32);
template const soCollisionAttackPart& soArrayVectorAbstract<soCollisionAttackPart>::at(s32) const;
template void soArrayVectorAbstract<soCollisionAttackPart>::unshift(const soCollisionAttackPart&);
template void soArrayVectorAbstract<soCollisionAttackPart>::shift();
template void soArrayVectorAbstract<soCollisionAttackPart>::push(const soCollisionAttackPart&);
template void soArrayVectorAbstract<soCollisionAttackPart>::pop();
template void soArrayVectorAbstract<soCollisionAttackPart>::insert(s32, const soCollisionAttackPart&);
template void soArrayVectorAbstract<soCollisionAttackPart>::erase(s32);
template void soArrayVectorAbstract<soCollisionAttackPart>::set(s32, const soCollisionAttackPart&, s32);
template void soArrayVectorAbstract<soCollisionAttackPart>::clear();
template bool soArrayVectorAbstract<soCollisionAttackPart>::isNull() const;
template void soArrayVectorAbstract<soCollisionAttackPart>::substitution(s32, s32);
