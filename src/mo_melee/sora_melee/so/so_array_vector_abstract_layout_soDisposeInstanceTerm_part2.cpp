#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soDisposeInstanceTerm.h>

template soDisposeInstanceTerm& soArrayVectorAbstract<soDisposeInstanceTerm>::at(s32);
template const soDisposeInstanceTerm& soArrayVectorAbstract<soDisposeInstanceTerm>::at(s32) const;
template void soArrayVectorAbstract<soDisposeInstanceTerm>::unshift(const soDisposeInstanceTerm&);
template void soArrayVectorAbstract<soDisposeInstanceTerm>::shift();
template void soArrayVectorAbstract<soDisposeInstanceTerm>::pop();
template void soArrayVectorAbstract<soDisposeInstanceTerm>::insert(s32, const soDisposeInstanceTerm&);
template void soArrayVectorAbstract<soDisposeInstanceTerm>::erase(s32);
template void soArrayVectorAbstract<soDisposeInstanceTerm>::set(s32, const soDisposeInstanceTerm&, s32);
template bool soArrayVectorAbstract<soDisposeInstanceTerm>::isNull() const;
template void soArrayVectorAbstract<soDisposeInstanceTerm>::substitution(s32, s32);
