#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soCollisionAttackAbsolute.h>

template soCollisionAttackAbsolute& soArrayVectorAbstract<soCollisionAttackAbsolute>::at(s32);
template const soCollisionAttackAbsolute& soArrayVectorAbstract<soCollisionAttackAbsolute>::at(s32) const;
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::unshift(const soCollisionAttackAbsolute&);
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::shift();
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::push(const soCollisionAttackAbsolute&);
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::pop();
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::insert(s32, const soCollisionAttackAbsolute&);
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::erase(s32);
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::set(s32, const soCollisionAttackAbsolute&, s32);
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::clear();
template bool soArrayVectorAbstract<soCollisionAttackAbsolute>::isNull() const;
template void soArrayVectorAbstract<soCollisionAttackAbsolute>::substitution(s32, s32);
