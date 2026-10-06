#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLogAttackInfo.h>

template soLogAttackInfo& soArrayVectorAbstract<soLogAttackInfo>::at(s32);
template const soLogAttackInfo& soArrayVectorAbstract<soLogAttackInfo>::at(s32) const;
template void soArrayVectorAbstract<soLogAttackInfo>::shift();
template void soArrayVectorAbstract<soLogAttackInfo>::push(const soLogAttackInfo&);
template void soArrayVectorAbstract<soLogAttackInfo>::insert(s32, const soLogAttackInfo&);
template void soArrayVectorAbstract<soLogAttackInfo>::erase(s32);
template void soArrayVectorAbstract<soLogAttackInfo>::set(s32, const soLogAttackInfo&, s32);
template bool soArrayVectorAbstract<soLogAttackInfo>::isNull() const;
template void soArrayVectorAbstract<soLogAttackInfo>::substitution(s32, s32);
