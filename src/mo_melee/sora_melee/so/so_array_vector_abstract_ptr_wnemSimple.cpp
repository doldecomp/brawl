#pragma force_active on
#include <so/so_array.h>

class wnemSimple;

template wnemSimple*& soArrayVectorAbstract<wnemSimple*>::at(s32);
template wnemSimple* const& soArrayVectorAbstract<wnemSimple*>::at(s32) const;
template void soArrayVectorAbstract<wnemSimple*>::unshift(wnemSimple* const&);
template void soArrayVectorAbstract<wnemSimple*>::shift();
template void soArrayVectorAbstract<wnemSimple*>::push(wnemSimple* const&);
template void soArrayVectorAbstract<wnemSimple*>::pop();
template void soArrayVectorAbstract<wnemSimple*>::insert(s32, wnemSimple* const&);
template void soArrayVectorAbstract<wnemSimple*>::erase(s32);
template void soArrayVectorAbstract<wnemSimple*>::set(s32, wnemSimple* const&, s32);
template void soArrayVectorAbstract<wnemSimple*>::clear();
template bool soArrayVectorAbstract<wnemSimple*>::isNull() const;
template void soArrayVectorAbstract<wnemSimple*>::substitution(s32, s32);
