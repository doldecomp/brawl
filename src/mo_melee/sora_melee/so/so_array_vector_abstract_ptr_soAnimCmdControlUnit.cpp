#pragma force_active on
#include <so/so_array.h>

class soAnimCmdControlUnit;

template soAnimCmdControlUnit*& soArrayVectorAbstract<soAnimCmdControlUnit*>::at(s32);
template soAnimCmdControlUnit* const& soArrayVectorAbstract<soAnimCmdControlUnit*>::at(s32) const;
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::unshift(soAnimCmdControlUnit* const&);
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::shift();
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::push(soAnimCmdControlUnit* const&);
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::pop();
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::insert(s32, soAnimCmdControlUnit* const&);
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::erase(s32);
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::set(s32, soAnimCmdControlUnit* const&, s32);
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::clear();
template bool soArrayVectorAbstract<soAnimCmdControlUnit*>::isNull() const;
template void soArrayVectorAbstract<soAnimCmdControlUnit*>::substitution(s32, s32);
