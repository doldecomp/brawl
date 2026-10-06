#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soShakeTerm.h>

template soShakeTerm& soArrayVectorAbstract<soShakeTerm>::at(s32);
template const soShakeTerm& soArrayVectorAbstract<soShakeTerm>::at(s32) const;
template void soArrayVectorAbstract<soShakeTerm>::unshift(const soShakeTerm&);
template void soArrayVectorAbstract<soShakeTerm>::shift();
template void soArrayVectorAbstract<soShakeTerm>::push(const soShakeTerm&);
template void soArrayVectorAbstract<soShakeTerm>::pop();
template void soArrayVectorAbstract<soShakeTerm>::insert(s32, const soShakeTerm&);
template void soArrayVectorAbstract<soShakeTerm>::erase(s32);
template void soArrayVectorAbstract<soShakeTerm>::set(s32, const soShakeTerm&, s32);
template void soArrayVectorAbstract<soShakeTerm>::clear();
template bool soArrayVectorAbstract<soShakeTerm>::isNull() const;
template void soArrayVectorAbstract<soShakeTerm>::substitution(s32, s32);
