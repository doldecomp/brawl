#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_damage.h>


template soDamage& soArrayVectorAbstract<soDamage>::at(s32);
template const soDamage& soArrayVectorAbstract<soDamage>::at(s32) const;
template void soArrayVectorAbstract<soDamage>::unshift(const soDamage&);
template void soArrayVectorAbstract<soDamage>::shift();
template void soArrayVectorAbstract<soDamage>::push(const soDamage&);
template void soArrayVectorAbstract<soDamage>::pop();
template void soArrayVectorAbstract<soDamage>::insert(s32, const soDamage&);
template void soArrayVectorAbstract<soDamage>::erase(s32);
template void soArrayVectorAbstract<soDamage>::set(s32, const soDamage&, s32);
template void soArrayVectorAbstract<soDamage>::clear();
template bool soArrayVectorAbstract<soDamage>::isNull() const;
template void soArrayVectorAbstract<soDamage>::substitution(s32, s32);
