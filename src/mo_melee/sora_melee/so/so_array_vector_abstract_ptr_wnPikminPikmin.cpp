#pragma force_active on
#include <so/so_array.h>

class wnPikminPikmin;

template wnPikminPikmin*& soArrayVectorAbstract<wnPikminPikmin*>::at(s32);
template wnPikminPikmin* const& soArrayVectorAbstract<wnPikminPikmin*>::at(s32) const;
template void soArrayVectorAbstract<wnPikminPikmin*>::unshift(wnPikminPikmin* const&);
template void soArrayVectorAbstract<wnPikminPikmin*>::shift();
template void soArrayVectorAbstract<wnPikminPikmin*>::push(wnPikminPikmin* const&);
template void soArrayVectorAbstract<wnPikminPikmin*>::pop();
template void soArrayVectorAbstract<wnPikminPikmin*>::insert(s32, wnPikminPikmin* const&);
template void soArrayVectorAbstract<wnPikminPikmin*>::erase(s32);
template void soArrayVectorAbstract<wnPikminPikmin*>::set(s32, wnPikminPikmin* const&, s32);
template void soArrayVectorAbstract<wnPikminPikmin*>::clear();
template bool soArrayVectorAbstract<wnPikminPikmin*>::isNull() const;
template void soArrayVectorAbstract<wnPikminPikmin*>::substitution(s32, s32);
